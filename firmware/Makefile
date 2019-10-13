
all: main.elf

main.elf: main.c stm32.ld
	arm-none-eabi-gcc -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -o main.elf -Wall -Wpedantic -Wstrict-aliasing -O0 -Wl,-Tstm32.ld main.c

.PHONY: clean
clean:
	rm -f main.elf
