CFLAGS := \
	-Iinclude \
	--target=riscv32 \
	-march=rv32i \
	-mabi=ilp32 \
	-ffreestanding \
	-nostdlib \
	-O3

LDFLAGS := \
	-m elf32lriscv \
	-T linker.ld

.PHONY: all firmware image clean

all: firmware image
firmware: bin/firmware.lst
image: bin/image.txt
clean:
	rm -rf build
	rm -rf bin

build/%.o: src/%.c
	clang $(CFLAGS) -c $< -o $@

build/%.o: src/%.s
	clang $(CFLAGS) -c $< -o $@

build/firmware.elf: $(wildcard build/*.o)
	ld.lld $(LDFLAGS) $^ -o $@

bin/firmware.lst: build/firmware.elf
	mkdir -p bin
	llvm-objdump -D -f -S $< > $@

build/image.bin: build/firmware.elf
	llvm-objcopy -O binary $< $@

bin/image.txt: build/image.bin
	od -j 4 -An -t x4 -v -w4 $< | xargs -n1 printf '0x%s\n' > $@