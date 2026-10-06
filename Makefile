CFLAGS = \
	-Iinclude \
	--target=riscv32 \
	-march=rv32i \
	-mabi=ilp32 \
	-ffreestanding \
	-nostdlib \
	-O3

LDFLAGS = \
	-m elf32lriscv \
	-T linker.ld

OBJDMPFLAGS = \
	-D \
	-f \
	-S

OBJCPYFLAGS = \
	-O binary \

bin/firmware.lst: build/firmware.elf
	mkdir -p bin
	llvm-objdump $(OBJDMPFLAGS) $^ > $@

build/firmware.elf: build/start.o build/main.o build/math.o
	ld.lld $(LDFLAGS) $^ -o $@

build/start.o: src/start.S
	mkdir -p build
	clang $(CFLAGS) -c $^ -o $@

build/main.o: src/main.c
	mkdir -p build
	clang $(CFLAGS) -c $^ -o $@

build/math.o: src/math.c
	mkdir -p build
	clang $(CFLAGS) -c $^ -o $@

build/image.bin: build/firmware.elf
	llvm-objcopy $(OBJCPYFLAGS) $^ $@

bin/image.txt: build/image.bin
	od -j 4 -An -t x4 -v -w4 $^ | xargs -n1 printf '0x%s\n' >> $@

clean:
	rm -rf build
	rm -rf bin