`default_nettype none

// Triangle oscillator, full amplitude output.
// Clock: 200 kHz  (info.yaml: clock_hz: 200000)
// Sample rate: clk/4 = 50 kHz
// Phase accumulator: 16-bit
module synth (
    input  wire        clk,
    input  wire        rst_n,
    input  wire  [5:0] midi_note,    // note index 0-63 → MIDI 36-99 (C2-Eb7)
    output wire [11:0] audio_sample, // unsigned 12-bit for simulation
    output reg         audio_out     // 1-bit sigma-delta PWM
);

// ── Sample clock divider: /4 → 50 kHz ──────────────────────────────────────
reg [1:0] sample_div;
wire sample_tick = &sample_div;

// ── Oscillators ─────────────────────────────────────────────────────────────
reg [15:0] phase;
reg [15:0] phase_inc;

// LFO: ~5 Hz triangle at 50 kHz (increment = round(5/50000*65536) = 7)
reg [15:0] lfo_phase;
wire [15:0] lfo_tri = lfo_phase[15] ? ~lfo_phase : lfo_phase; // [0..32767]
// Map to signed ±8 offset: (lfo_tri − 16384) >> 11  →  [−8..7]
wire signed [15:0] lfo_offset = ($signed(lfo_tri) - 16'sd16384) >>> 11;
// Second phase accumulator detuned by the LFO
reg [15:0] phase2;
wire [15:0] phase2_inc = 16'($signed(phase_inc) + lfo_offset);

// Fold each phase to a triangle, take top 11 bits
wire [10:0] tri_wave  = 11'((phase[15]  ? ~phase  : phase)  >> 4);
wire [10:0] tri_wave2 = 11'((phase2[15] ? ~phase2 : phase2) >> 4);
// Square wave at 4× the fundamental from the primary oscillator
wire [10:0] sq_wave = {4'b0000, {7{phase[13]}}};
// Mix all three; sum fits in 13 bits (max 4349), shift right 1 → 12-bit output
wire [12:0] raw_mix = {2'b0, tri_wave} + {2'b0, tri_wave2} + {2'b0, sq_wave};
assign audio_sample = raw_mix[12:1];

// ── Sigma-delta modulator (runs at full 200 kHz) ────────────────────────────
reg [11:0] sd_accum;
wire [12:0] sd_next = sd_accum + audio_sample;

// ── Note frequency: 12-entry semitone table + octave shift ──────────────────
// phase_inc = base_inc[note % 12] << (note / 12)
// base_inc holds one octave at 50 kHz / 16-bit accumulator (MIDI 36-47).
// Doubling every octave is exact; rounding error on the base values is
// ≤ 0.5 LSB, which shifts by at most 2^5 = 32 → < 0.1% tuning error at top.
reg [7:0] base_inc;
reg [2:0] octave;
reg [3:0] semitone;

always @(*) begin
    // Octave (note / 12) and semitone (note % 12) via comparison chain
    if      (midi_note >= 6'd60) begin octave = 3'd5; semitone = 4'(midi_note - 6'd60); end
    else if (midi_note >= 6'd48) begin octave = 3'd4; semitone = 4'(midi_note - 6'd48); end
    else if (midi_note >= 6'd36) begin octave = 3'd3; semitone = 4'(midi_note - 6'd36); end
    else if (midi_note >= 6'd24) begin octave = 3'd2; semitone = 4'(midi_note - 6'd24); end
    else if (midi_note >= 6'd12) begin octave = 3'd1; semitone = 4'(midi_note - 6'd12); end
    else                         begin octave = 3'd0; semitone = 4'(midi_note);          end
end

always @(*) begin
    // 12 base increments for MIDI 36-47 (C2-B2) at 50 kHz, 16-bit accumulator
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

always @(*) phase_inc = {8'b0, base_inc} << octave;

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        sample_div <= 2'b0;
        phase      <= 16'b0;
        phase2     <= 16'b0;
        lfo_phase  <= 16'b0;
        sd_accum   <= 12'b0;
        audio_out  <= 1'b0;
    end else begin
        sd_accum  <= sd_next[11:0];
        audio_out <= sd_next[12];

        sample_div <= sample_div + 1;
        if (sample_tick) begin
            phase     <= phase     + phase_inc;
            phase2    <= phase2    + phase2_inc;
            lfo_phase <= lfo_phase + 16'd5;
        end

    end
end

endmodule
