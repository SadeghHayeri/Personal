.data 0x10000000
.word 3, 2, 1, 7, 1, 2, 42, 42, 22, 12, 94, 21, 20, 0, 32, 42, 12, 31, 213, 123, 421, 2, 23, 12, 53
nl: .asciiz "\n" # New line
.text

.globl main
main:

li $t0, 0x0 # i
li $t2, 0x64 # End(100)

fori:
  addi $t1, $t0, 0x0 # j

  forj:
    li $t3, 0x10000000
    add $t3, $t3, $t0 # Address of A[i]
    li $t4, 0x10000000
    add $t4, $t4, $t1 # Address of A[j]
    lw $t5, ($t3) # A[i]
    lw $t6, ($t4) # A[j]

    bge $t5, $t6, end # if( A[i] < A[j] )
      addi $t7, $t5, 0x0 # temp = A[i]
      sw $t6, ($t3) # A[i] = A[j]
      sw $t7, ($t4) # A[j] = temp
    end:

    addi $t1, $t1, 0x4
    bne $t1, $t2, forj

  addi $t0, $t0, 0x4
  bne $t0, $t2, fori

li $t0, 0x0
print: # 25 times
  li $t1, 0x10000000
  add $t1, $t1, $t0 # Address of number
  li $v0, 0x1
  lw $a0, ($t1)
  syscall # Print number
  li $v0, 4
  la $a0, nl
  syscall # Print new line

  addi $t0, $t0, 0x4
  bne $t0, $t2, print

li $v0, 0xa
syscall # Exit
