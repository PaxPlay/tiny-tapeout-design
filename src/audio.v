`default_nettype none

module cool_audio(
    input wire clk,
    input wire rst,
    output reg out);

  reg [15:0] audio_sample;
  reg [15:0] sigma_delta_accum;

  wire [16:0] _sigma_delta_accum = sigma_delta_accum + audio_sample;

  always @(posedge clk or negedge rst) begin
    if (~rst) begin
      sigma_delta_accum <= 0;
    end else begin
      sigma_delta_accum <= _sigma_delta_accum[15:0];
      out <= _sigma_delta_accum[16];
    end
  end
endmodule

