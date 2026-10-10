MAKEFLAGS += -r

CFLAGS := \
	-Iinclude \
	--target=riscv32 \
	-march=rv32i \
	-mabi=ilp32 \
	-nostdlib \
	-O3 \
	-g

LDFLAGS := \
	-m elf32lriscv \
	-T linker.ld

objects := build/main.o build/math.o build/models.o build/rendering.o build/start.o

.PHONY: all firmware image clean

all: firmware image
firmware: bin/firmware.lst
image: bin/image.txt
clean:
	rm -rf build
	rm -rf bin

build/%.o: src/%.c
	mkdir -p build
	clang $(CFLAGS) -c $< -o $@

build/%.o: src/%.s
	mkdir -p build
	clang $(CFLAGS) -c $< -o $@

build/firmware.elf: $(objects)
	mkdir -p build
	ld.lld $(LDFLAGS) $^ -o $@

bin/firmware.lst: build/firmware.elf
	mkdir -p bin
	llvm-objdump -D -f -S $< > $@

build/image.bin: build/firmware.elf
	llvm-objcopy -O binary $< $@

bin/image.txt: build/image.bin
	od -j 4 -An -t x4 -v -w4 $< | xargs -n1 printf '0x%s\n' > $@
	cp $@ ~/VCB/limonene.vcbasm