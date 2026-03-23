/*
 * Copyright (c) 2024 Benedikt Krimmel
 * SPDX-License-Identifier: Apache-2.0
 */

`default_nettype none

module tt_um_krimmel_mini_synth (
    input  wire [7:0] ui_in,    // [5:0] note index (MIDI 36-99)
    output wire [7:0] uo_out,   // [7] = audio PWM (AudioPWM on uo[7])
    input  wire [7:0] uio_in,
    output wire [7:0] uio_out,
    output wire [7:0] uio_oe,
    input  wire       ena,
    input  wire       clk,
    input  wire       rst_n
);

    wire [5:0] midi_note = ui_in[5:0];
    wire audio_pwm;

    synth synth_inst (
        .clk        (clk),
        .rst_n      (rst_n),
        .midi_note  (midi_note),
        .audio_sample(),         // not connected at top level
        .audio_out  (audio_pwm)
    );

    assign uo_out  = {audio_pwm, 7'b0};  // audio on uo[7] per info.yaml
    assign uio_out = 8'b0;
    assign uio_oe  = 8'b0;

    wire _unused = &{ena, uio_in, ui_in[7:6], 1'b0};


endmodule
