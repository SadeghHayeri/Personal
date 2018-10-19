`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    17:59:09 11/08/2017
// Design Name:
// Module Name:    main
// Project Name:
// Target Devices:
// Tool versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////
module main(
      clk,
      data_in,
      start,
      rst,
      data_out,
      done
    );

    input clk;
    input [7:0] data_in;
    input start, rst;
    output [7:0] data_out;
    output done;

    wire addgen_comp_9, addgen_comp_18, row_comp, col_comp, item_comp, m1_write;
    wire m2_write, res_ld, res_rst, addgen_cn, addgen_rst, row_cn, row_rst;
    wire col_cn, col_rst, item_cn, item_rst, m1_sel, m2_sel, fm_sel, out_sel;
    wire fm_write;

    DataPath dp(
      clk, data_in, data_out, addgen_comp_9, addgen_comp_18, row_comp, col_comp,
      item_comp, m1_write, m2_write, fm_write, res_ld, res_rst, addgen_cn, addgen_rst,
      row_cn, row_rst, col_cn, col_rst, item_cn, item_rst, m1_sel, m2_sel, fm_sel, out_sel
    );

    Controller cu(
      clk, rst, start, m1_write, m2_write, fm_write, m1_sel, m2_sel, fm_sel, out_sel,
      res_ld, res_rst, addgen_rst, addgen_cn, row_rst, row_cn, col_rst, col_cn,
      item_rst, item_cn, addgen_comp_9, addgen_comp_18, row_comp, col_comp, item_comp, done
    );

endmodule
