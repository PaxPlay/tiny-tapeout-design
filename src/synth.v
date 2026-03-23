`default_nettype none

// Triangle + LFO-detuned triangle + square + LFO-detuned sawtooth oscillators with ADSR envelope.
// Clock:       50 MHz  (info.yaml: clock_hz: 50000000)
// Sample rate: 50 MHz / 1000 = 50 kHz
// Envelope:    pulse-density control — 7-bit chop counter, period 125, at 50 MHz
//              f_chop = 400 kHz, well above the audio pmod RC filter cutoff
module synth (
    input  wire        clk,
    input  wire        rst_n,
    input  wire  [6:0] midi_note,    // MIDI note 0-127
    input  wire        gate,         // 1 = note on
    output wire [11:0] audio_sample, // unsigned 12-bit for simulation
    output reg         audio_out     // 1-bit sigma-delta PWM
);

// ── Sample clock divider: 50 MHz / 1000 = 50 kHz ───────────────────────────
reg [9:0] sample_div;
wire sample_tick = (sample_div == 10'd999);

// ── Oscillators ─────────────────────────────────────────────────────────────
reg [15:0] phase;
reg [15:0] phase_inc;

// LFO: ~4 Hz triangle (increment 5 at 50 kHz → 5/65536*50000 ≈ 3.8 Hz)
reg [15:0] lfo_phase;
wire [15:0] lfo_tri = lfo_phase[15] ? ~lfo_phase : lfo_phase;
wire signed [15:0] lfo_offset = ($signed(lfo_tri) - 16'sd16384) >>> 11;

// Osc 2: triangle at same pitch, +lfo_offset (chorus detune)
reg [15:0] phase2;
wire [15:0] phase2_inc = 16'($signed(phase_inc) + lfo_offset);

// Osc 3: sawtooth at 2× pitch, -lfo_offset (counter-detune)
reg [15:0] phase3;
wire [15:0] phase3_inc = 16'($signed(phase_inc + phase_inc) - (lfo_offset >>> 2));

wire [10:0] tri_wave  = 11'((phase[15]  ? ~phase  : phase)  >> 4);
wire [10:0] tri_wave2 = 11'((phase2[15] ? ~phase2 : phase2) >> 4);
wire [10:0] sq_wave   = {5'b00000, {6{phase[13]}}};
wire [10:0] saw_wave  = {2'b0, phase3[15:7]};   // sawtooth: raw phase, upper 11 bits

wire [12:0] raw_mix   = {2'b0, tri_wave} + {2'b0, tri_wave2} + {2'b0, sq_wave} + {2'b0, saw_wave};
wire [11:0] raw_audio = raw_mix[12:1];

// ── ADSR envelope via pulse density amplitude control ───────────────────────
// chop_ctr is a free-running 7-bit counter (period 125) at 50 MHz.
// audio_sample = raw_audio when chop_ctr < vol, else 12'h800 (midpoint/silence).
// Period 125 divides sample period 1000 exactly (8 chop cycles/sample) →
// no aliasing tone.  f_chop = 50 MHz / 125 = 400 kHz, well above RC cutoff.
// vol range 0-125 maps to 0-100% duty cycle.
//
// ADSR timing (all derived from power-of-2 sample counts — no extra divider):
//   Attack:  vol++ every  4 samples → 125 steps *  4 / 50000 ≈  10 ms
//   Decay:   vol-- every 16 samples →  47 steps * 16 / 50000 ≈  15 ms (to sustain)
//   Release: vol-- every 32 samples →  78 steps * 32 / 50000 ≈  50 ms

localparam IDLE    = 3'd0;
localparam ATTACK  = 3'd1;
localparam DECAY   = 3'd2;
localparam SUSTAIN = 3'd3;
localparam RELEASE = 3'd4;
localparam [7:0] SUSTAIN_LEVEL = 8'd68;

reg [2:0] adsr_state;
reg [7:0] vol;
reg [5:0] adsr_ctr;   // free-running, incremented each sample_tick
reg       gate_prev;
reg [6:0] chop_ctr;   // free-running at full 50 MHz, period 125

wire attack_tick  = sample_tick && (adsr_ctr[2:0] == 3'b000);
wire decay_tick   = sample_tick && (adsr_ctr[4:0] == 5'b00000);
wire release_tick = sample_tick && (adsr_ctr[5:0] == 6'b000000);

assign audio_sample = ({1'b0, chop_ctr} < vol) ? raw_audio : 12'h800;

// ── Sigma-delta modulator (runs at full 50 MHz) ─────────────────────────────
reg [11:0] sd_accum;
wire [12:0] sd_next = sd_accum + audio_sample;

// ── Note frequency: 12-entry semitone table + octave shift ──────────────────
// Base increments correspond to C2 (MIDI 36) for high precision.
// For MIDI >= 36: phase_inc = base_inc << octave  (left shift, above C2)
// For MIDI <  36: phase_inc = base_inc >> octave  (right shift, below C2)
reg [7:0] base_inc;
reg [2:0] octave;
reg [3:0] semitone;
reg       below_c2;

always @(*) begin
    if      (midi_note >= 7'd120) begin below_c2 = 0; octave = 3'd7; semitone = 4'(midi_note - 7'd120); end
    else if (midi_note >= 7'd108) begin below_c2 = 0; octave = 3'd6; semitone = 4'(midi_note - 7'd108); end
    else if (midi_note >= 7'd96)  begin below_c2 = 0; octave = 3'd5; semitone = 4'(midi_note - 7'd96);  end
    else if (midi_note >= 7'd84)  begin below_c2 = 0; octave = 3'd4; semitone = 4'(midi_note - 7'd84);  end
    else if (midi_note >= 7'd72)  begin below_c2 = 0; octave = 3'd3; semitone = 4'(midi_note - 7'd72);  end
    else if (midi_note >= 7'd60)  begin below_c2 = 0; octave = 3'd2; semitone = 4'(midi_note - 7'd60);  end
    else if (midi_note >= 7'd48)  begin below_c2 = 0; octave = 3'd1; semitone = 4'(midi_note - 7'd48);  end
    else if (midi_note >= 7'd36)  begin below_c2 = 0; octave = 3'd0; semitone = 4'(midi_note - 7'd36);  end
    else if (midi_note >= 7'd24)  begin below_c2 = 1; octave = 3'd1; semitone = 4'(midi_note - 7'd24);  end
    else if (midi_note >= 7'd12)  begin below_c2 = 1; octave = 3'd2; semitone = 4'(midi_note - 7'd12);  end
    else                          begin below_c2 = 1; octave = 3'd3; semitone = 4'(midi_note);           end
end

always @(*) begin
    case (semitone)
        4'd0:  base_inc = 8'd86;   // C
        4'd1:  base_inc = 8'd91;   // C#
        4'd2:  base_inc = 8'd96;   // D
        4'd3:  base_inc = 8'd102;  // D#
        4'd4:  base_inc = 8'd108;  // E
        4'd5:  base_inc = 8'd114;  // F
        4'd6:  base_inc = 8'd121;  // F#
        4'd7:  base_inc = 8'd128;  // G
        4'd8:  base_inc = 8'd136;  // G#
        4'd9:  base_inc = 8'd144;  // A
        4'd10: base_inc = 8'd153;  // A#
        4'd11: base_inc = 8'd162;  // B
        default: base_inc = 8'd0;
    endcase
end

always @(*) phase_inc = below_c2 ? ({8'b0, base_inc} >> octave) : ({8'b0, base_inc} << octave);

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        sample_div <= 10'b0;
        phase      <= 16'b0;
        phase2     <= 16'b0;
        phase3     <= 16'b0;
        lfo_phase  <= 16'b0;
        adsr_state <= IDLE;
        vol        <= 8'b0;
        adsr_ctr   <= 6'b0;
        gate_prev  <= 1'b0;
        chop_ctr   <= 7'b0;
        sd_accum   <= 12'b0;
        audio_out  <= 1'b0;
    end else begin
        // Full clock-rate updates
        sd_accum  <= sd_next[11:0];
        audio_out <= sd_next[12];
        chop_ctr  <= (chop_ctr == 7'd124) ? 7'b0 : chop_ctr + 1;

        // Sample-rate updates
        sample_div <= sample_tick ? 10'b0 : sample_div + 1;
        if (sample_tick) begin
            phase     <= phase     + phase_inc;
            phase2    <= phase2    + phase2_inc;
            phase3    <= phase3    + phase3_inc;
            lfo_phase <= lfo_phase + 16'd3;

            adsr_ctr  <= adsr_ctr + 1;
            gate_prev <= gate;

            case (adsr_state)
                IDLE: begin
                    if (gate && !gate_prev) begin
                        adsr_state <= ATTACK;
                        vol        <= 8'b0;
                    end
                end
                ATTACK: begin
                    if (!gate) begin
                        adsr_state <= RELEASE;
                    end else if (attack_tick) begin
                        if (vol == 8'd125) adsr_state <= DECAY;
                        else               vol <= vol + 1;
                    end
                end
                DECAY: begin
                    if (!gate) begin
                        adsr_state <= RELEASE;
                    end else if (decay_tick) begin
                        if (vol <= SUSTAIN_LEVEL) begin
                            adsr_state <= SUSTAIN;
                            vol        <= SUSTAIN_LEVEL;
                        end else
                            vol <= vol - 1;
                    end
                end
                SUSTAIN: begin
                    if (!gate) adsr_state <= RELEASE;
                end
                RELEASE: begin
                    if (gate && !gate_prev) begin
                        adsr_state <= ATTACK;
                        vol        <= 8'b0;
                    end else if (release_tick) begin
                        if (vol == 8'b0) adsr_state <= IDLE;
                        else             vol <= vol - 1;
                    end
                end
                default: adsr_state <= IDLE;
            endcase
        end
    end
end

endmodule
