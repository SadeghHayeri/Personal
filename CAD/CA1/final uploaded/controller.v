`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    17:57:34 11/08/2017
// Design Name:
// Module Name:    controller
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
module Controller(
  clk,
  rst,
  start,
  m1_write,
  m2_write,
  fm_write,
  m1_sel,
  m2_sel,
  fm_sel,
  out_sel,
  res_ld,
  res_rst,
  addgen_rst,
  addgen_cn,
  row_rst,
  row_cn,
  col_rst,
  col_cn,
  item_rst,
  item_cn,
  addgen_comp_9,
  addgen_comp_18,
  row_comp,
  col_comp,
  item_comp,
  done
  );

  input clk, rst, start;
  input addgen_comp_9, addgen_comp_18;
  input row_comp, col_comp, item_comp;
  output reg m1_write, m2_write, fm_write;
  output reg m1_sel, m2_sel;
  output reg [1:0] out_sel;
  output reg res_ld;
  output reg res_rst, fm_sel;
  output reg addgen_rst, addgen_cn;
  output reg row_rst, row_cn;
  output reg col_rst, col_cn;
  output reg item_rst, item_cn;
  output reg done;

  localparam[3:0] wait_for_start = 4'd0, starting = 4'd1, read_memory1 = 4'd2, read_memory2 = 4'd3, item_switch = 4'd4, col_switch = 4'd5, row_switch = 4'd6, ready_to_out = 4'd7, part1 = 4'd8, part2 = 4'd9, part3 = 4'd10, reset = 4'd11, pre_part = 4'd12;
  reg [3:0] ps, ns = 4'd0;

  always @ (posedge clk, posedge rst) begin
    if( rst == 1'b1 )
      ps <= wait_for_start;
    else
      ps <= ns;
  end

  always @ ( * ) begin

    m1_write <= 0;
    m2_write <= 0;
    fm_write <= 0;

    m1_sel <= 0;
    m2_sel <= 0;
    fm_sel <= 0;
    out_sel <= 0;

    res_ld <= 0;
    res_rst <= 0;

    addgen_rst <= 0;
    addgen_cn <= 0;
    row_rst <= 0;
    row_cn <= 0;
    col_rst <= 0;
    col_cn <= 0;
    item_rst <= 0;
    item_cn <= 0;

    done <= 0;

    case (ps)
    wait_for_start: begin

    end
    starting: begin
      addgen_rst <= 1;
      res_rst <= 1;
      row_rst <= 1;
      col_rst <= 1;
      item_rst <= 1;
    end
    read_memory1: begin
      m1_sel <= 1;
      m1_write  <= 1;
      addgen_cn <= 1;
    end
    read_memory2: begin
      m2_sel <= 1;
      m2_write <= 1;
      addgen_cn <= 1;
    end
    item_switch: begin
      item_cn <= 1;
      m1_sel <= 0;
      m2_sel <= 0;
      res_ld <= 1;
    end
    col_switch: begin
      item_rst <= 1;
      col_cn <= 1;
      fm_write <= 1;
      fm_sel <= 1;
    end
    row_switch: begin
      col_rst <= 1;
      row_cn <= 1;
    end
    ready_to_out: begin
      done <= 1;
      addgen_rst <= 1;
    end
    part1: begin
      out_sel <= 2'b00;
      fm_sel <= 0;
    end
    part2: begin
      out_sel <= 2'b01;
      fm_sel <= 0;
    end
    part3: begin
      out_sel <= 2'b10;
      fm_sel <= 0;
    end
    reset: begin
      res_rst <= 1;
    end
    pre_part: begin
      addgen_cn <= 1;
    end
    endcase

  end

  always @ ( * ) begin
    ns = wait_for_start;
    case (ps)
      wait_for_start: ns = (start == 1) ? starting : wait_for_start;
      starting: ns = (start == 0) ? read_memory1 : starting;
      read_memory1: ns = (addgen_comp_9 == 1) ? read_memory2 : read_memory1;
      read_memory2: ns = (addgen_comp_18 == 1) ? item_switch : read_memory2;
      item_switch: ns = (item_comp == 1) ? col_switch : item_switch;
      col_switch: ns = reset;
      row_switch: ns = (row_comp == 1) ? ready_to_out : item_switch;
      ready_to_out: ns = part1;
      part1: ns = part2;
      part2: ns = part3;
      part3: ns = pre_part;
      reset: ns = (col_comp == 1) ? row_switch : item_switch;
      pre_part: ns = (addgen_comp_9 == 1) ? wait_for_start : part1;
    endcase
  end

endmodule
