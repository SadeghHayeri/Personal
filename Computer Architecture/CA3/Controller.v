`timescale 1ns/1ns
//memsource= iord
//jz = jz
module Controller(input[2:0] opcode/*, input zero*/, input rst, clk,
  output reg AccSrc, output reg MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, PCsrc, PCwrite, jz,
  output reg[1:0] ALUop, Bsrc);



    parameter IF = 0, ID = 1, JZ = 2, JMP = 3, ADD = 4, SUB = 5, AND = 6, NOT = 7,  LDA = 8, STA = 9;
		reg [3:0]ps, ns;
		always@(posedge clk, posedge rst) begin
			if (clk)
				ps <= ns;
			else
				ps <= 0;
		end

		always @ (*) begin
			ns = IF;
			case (ps)
				IF: ns = ID;
				ID: if(opcode == 3'b0) ns = ADD; else if(opcode == 3'b001) ns = SUB; else if(opcode == 3'b010) ns = AND; else if(opcode == 3'b011) ns = NOT; else if(opcode == 3'b100) ns = LDA; else if(opcode == 3'b101) ns = STA; else if(opcode == 3'b110) ns = JMP; else if(opcode == 3'b111) ns = JZ;
				JZ: ns = IF;
				JMP: ns = IF;
				AND: ns = IF;
				SUB: ns = IF;
				ADD: ns = IF;
				NOT: ns = IF;
				LDA: ns = IF;
				STA: ns = IF;
				default: ns = IF;
			endcase
		end

		always @(ps) begin
			{AccSrc, MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, Bsrc, PCsrc, PCwrite, jz, ALUop} <= 14'b0;
			case(ps)
				IF : {PCsrc, PCwrite, ALUop, Asrc, Bsrc, ldIR, IorD, MemRead} <= 10'b0100001101;
				ID : {MemRead, IorD} <= 2'b11;
				ADD : {Asrc, Bsrc, ALUop, ldAcc, AccSrc} <= 7'b1100010;
				SUB : {Asrc, Bsrc, ALUop, ldAcc, AccSrc} <= 7'b1100110;
				AND : {Asrc, Bsrc, ALUop, ldAcc, AccSrc} <= 7'b1101010;
				NOT : {Asrc, Bsrc, ALUop, ldAcc, AccSrc} <= 7'b1xx1110;
				JMP : {PCwrite, PCsrc} <= 2'b11;
				JZ : {Asrc, Bsrc, ALUop, jz, PCsrc} <= 7'b1000111;
				LDA : {ldAcc, AccSrc} <= 2'b11;
				STA : {MemWrite, IorD} <= 2'b11;
			endcase
		end
endmodule
