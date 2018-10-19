`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    17:56:05 11/08/2017
// Design Name:
// Module Name:    datapath
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
module DataPath(
  clk,
  data_in,
  data_out,
  addgen_comp_9,
  addgen_comp_18,
  row_comp,
  col_comp,
  item_comp,
  m1_write,
  m2_write,
  fm_write,
  res_ld,
  res_rst,
  addgen_cn,
  addgen_rst,
  row_cn,
  row_rst,
  col_cn,
  col_rst,
  item_cn,
  item_rst,
  m1_sel,
  m2_sel,
  fm_sel,
  out_sel
);

    input clk;
    input [7:0] data_in;
    output  [7:0] data_out;
    output reg addgen_comp_9, addgen_comp_18, row_comp, col_comp, item_comp;

    input m1_write, m2_write, fm_write, res_ld, res_rst, addgen_cn, addgen_rst, row_cn, row_rst, col_cn, col_rst, item_cn, item_rst;
    input m1_sel, m2_sel, fm_sel;
    input [1:0] out_sel;

    wire [7:0] m1_out, m2_out;
    wire [17:0] res_in, res_out, fm_out;
    wire [4:0] addgen_out, addgen_out2; // count_out2 = count_out - 9
    wire [1:0] row_out, col_out, item_out;

    wire [3:0] m1_address, m2_address, fm_address;
    wire [3:0] a1_address, a2_address, a3_address;

    Memory #(8, 9, 4) M1(clk, m1_write, m1_address, data_in, m1_out);
    Memory #(8, 9, 4) M2(clk, m2_write, m2_address, data_in, m2_out);
    Memory #(18, 9, 4) Final_mem(clk, fm_write, fm_address, res_out, fm_out);

    Mux2 #(4) Mux_address1(a1_address, addgen_out[3:0], m1_sel, m1_address);
    Mux2 #(4) Mux_address2(a2_address, addgen_out2[3:0], m2_sel, m2_address);
    Mux2 #(4) Mux_address3(addgen_out[3:0], a3_address, fm_sel, fm_address);
    Mux4 #(8) Mux_output(fm_out[7:0], fm_out[15:8], {6'd0, fm_out[17:16]}, 8'b0, out_sel, data_out);

    Register #(18) Res(clk, res_ld, res_rst, res_in, res_out);

    Counter #(5) Address_gen_counter(clk, addgen_rst, addgen_cn, addgen_out);
    Counter #(2) Row_counter(clk, row_rst, row_cn, row_out);
    Counter #(2) Col_counter(clk, col_rst, col_cn, col_out);
    Counter #(2) Item_counter(clk, item_rst, item_cn, item_out);

    assign res_in = (m1_out * m2_out + res_out);
    assign addgen_out2 = (addgen_out - 9);

    assign a1_address = (row_out * 3) + item_out;
    assign a2_address = (item_out * 3) + col_out;
    assign a3_address = (row_out * 3) + col_out;

    always @ ( * ) begin
      addgen_comp_9 <= (addgen_out == 8) ? 1'b1 : 1'b0;
      addgen_comp_18 <= (addgen_out == 17) ? 1'b1 : 1'b0;
      row_comp <= (row_out == 2) ? 1'b1 : 1'b0;
      col_comp <= (col_out == 2) ? 1'b1 : 1'b0;
      item_comp <= (item_out == 2) ? 1'b1 : 1'b0;
    end

endmodule
