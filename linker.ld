MEMORY {
    RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 4M
}

SECTIONS {
    .hardware 0x00000000 : {
        *(.hardware .hardware.*)
    } > RAM

    .text 0x00000040: {
        KEEP(*(.text.entry))
        *(.text .text.*)
    } > RAM

    .rodata : {
        *(.rodata .rodata.*)
    } > RAM

    .data : {
        *(.data .data.*)
    } > RAM

    .bss : {
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    } > RAM

    . = ALIGN(16);
    __stack_top = ORIGIN(RAM) + LENGTH(RAM);
}