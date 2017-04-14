list: .word 3, 2, 1, 0, 1, 2

main:
	move $s0, $gp			#get the intial point to save array
  la $t0, list

	lw $t1, 3($t0)
