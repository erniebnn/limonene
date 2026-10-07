.section .hardware, "a"
.global fptr
.word 0x0 // padding as address 0x0 is unusable
fptr: .word 0x0

.section .text
.global _start
.global set_fptr

_start:
    la sp, __stack_top
    la t0, __bss_start
    la t1, __bss_end
bssclear_loop:
    beq t0, t1, bssclear_end
    sw x0, 0x0(t0)
    addi t0, t0, 0x4
    j bssclear_loop
bssclear_end:
    call main
loop:
    j loop

set_fptr:
    la t0, fptr
    srli a0, a0, 0x2
    sw a0, 0x0(t0)
    ret