`default_nettype none

module sin(
    input wire clk,
    input wire rst,
    input wire [7:0] x,
    output wire [15:0] sin_x
);

  always @(posedge clk) begin
    sin_x <= rom_sin(x[5:0]);
  end

  function [14:0] rom_sin(input [5:0] _x);
    case (_x)
      00: rom_sin = 15'h0000;
      01: rom_sin = 15'h0324;
      02: rom_sin = 15'h0647;
      03: rom_sin = 15'h096a;
      04: rom_sin = 15'h0c8b;
      05: rom_sin = 15'h0fab;
      06: rom_sin = 15'h12c7;
      07: rom_sin = 15'h15e1;
      08: rom_sin = 15'h18f8;
      09: rom_sin = 15'h1c0b;
      10: rom_sin = 15'h1f19;
      11: rom_sin = 15'h2223;
      12: rom_sin = 15'h2527;
      13: rom_sin = 15'h2826;
      14: rom_sin = 15'h2b1e;
      15: rom_sin = 15'h2e10;
      16: rom_sin = 15'h30fb;
      17: rom_sin = 15'h33de;
      18: rom_sin = 15'h36b9;
      19: rom_sin = 15'h398c;
      20: rom_sin = 15'h3c56;
      21: rom_sin = 15'h3f16;
      22: rom_sin = 15'h41cd;
      23: rom_sin = 15'h447a;
      24: rom_sin = 15'h471c;
      25: rom_sin = 15'h49b3;
      26: rom_sin = 15'h4c3f;
      27: rom_sin = 15'h4ebf;
      28: rom_sin = 15'h5133;
      29: rom_sin = 15'h539a;
      30: rom_sin = 15'h55f4;
      31: rom_sin = 15'h5842;
      32: rom_sin = 15'h5a81;
      33: rom_sin = 15'h5cb3;
      34: rom_sin = 15'h5ed6;
      35: rom_sin = 15'h60eb;
      36: rom_sin = 15'h62f1;
      37: rom_sin = 15'h64e7;
      38: rom_sin = 15'h66ce;
      39: rom_sin = 15'h68a5;
      40: rom_sin = 15'h6a6c;
      41: rom_sin = 15'h6c23;
      42: rom_sin = 15'h6dc9;
      43: rom_sin = 15'h6f5e;
      44: rom_sin = 15'h70e1;
      45: rom_sin = 15'h7254;
      46: rom_sin = 15'h73b5;
      47: rom_sin = 15'h7503;
      48: rom_sin = 15'h7640;
      49: rom_sin = 15'h776b;
      50: rom_sin = 15'h7883;
      51: rom_sin = 15'h7989;
      52: rom_sin = 15'h7a7c;
      53: rom_sin = 15'h7b5c;
      54: rom_sin = 15'h7c29;
      55: rom_sin = 15'h7ce2;
      56: rom_sin = 15'h7d89;
      57: rom_sin = 15'h7e1c;
      58: rom_sin = 15'h7e9c;
      59: rom_sin = 15'h7f08;
      60: rom_sin = 15'h7f61;
      61: rom_sin = 15'h7fa6;
      62: rom_sin = 15'h7fd7;
      63: rom_sin = 15'h7ff5;
    endcase
  endfunction


endmodule

