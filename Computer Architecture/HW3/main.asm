.data 0x10000000

list: .word 3, 2, 1, 7, 1, 2
size: .word 6
nl: .asciiz "\n" # New line

.text
.globl main
main:
	move 	$s0, $gp		# $s0 = $gp
	lw		$t1, size		# load size of array to t1
	li		$t2, 0		# $t2 = 0	(i)

########## loopI
loopI:
	li		$t3, 0		# $t3 = 0	(j)

	########## loopII
	loopII:
		lw		$t4, list($t2)	# $t4 <- arr[i]
		lw		$t5, list($t3)	# $t5 <- arr[j]
		blt		$t5, $t4, afterIf	# if $t5 < $t4 then afterIf

		addi		$t7, $t4, 0		# $t7 = $t4 + 0
		addi		$t4, $t5, 0		# $t7 = $t4 + 0
		addi		$t5, $t7, 0		# $t7 = $t4 + 0
	afterIf:
		addi	$t3, $t3, 4			# $t3 = $t3 + 4
		blt		$t3, $t1, loopII	# if $t3 < $t1 then loopII
	########## end loopII

	addi		$t2, $t2, 4		# $t2 = $t2 + 4
	blt		$t2, $t1, loopI	# if $t2 < $t1 then loopI
########## end loopI
