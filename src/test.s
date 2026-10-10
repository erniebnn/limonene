.section .hardware, "a"
    .word 0x0 // padding word
    val0: .word 0x0
    val1: .word 0x0

.section .text.entry
.global _start
    _start:
        la sp, __stack_top
        call main
    end:
        j end

.section .text
    main:
        la t0, val0
        la t1, val1
    loop:
        mv t2, zero
        lw t2, 0x0(t0)
        addi t2, t2, 1
        sw t2, 0x0(t1)
        mv t3, zero
        lw t3, 0x0(t1)
        addi t3, t3, 1
        sw t3, 0x0(t0)
        j loop
        ret