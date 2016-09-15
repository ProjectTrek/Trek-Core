ARCH:=x86

CC:=i686-elf-gcc
CPP:=i686-elf-g++
LD:=i686-elf-ld
ASM:=nasm
KERNEL:=kernel.elf
C_FLAGS:=
LD_FLAGS:=
ASM_FLAGS:=

include kernel/arch/$(ARCH)/Makefile
include kernel/kernel/Makefile
include kernel/arch/$(ARCH)/config.make
include kernel/drivers/Makefile

C_FLAGS:=-ffreestanding -O2 -nostdlib -Ikernel/kernel -Ikernel/drivers -Ikernel/include kernel/arch/$(ARCH)
LD_FLAGS:=-Tkernel/arch/$(ARCH)/link.ld $(LD_FLAGS)
ASM_FLAGS:=-f elf $(ASM_FLAGS)

all: $(KERNEL)

$(KERNEL): $(OBJECTS)
	$(LD) $(LD_FLAGS) -o $(KERNEL) $(OBJECTS)

clean:
	-rm $(OBJECTS) $(KERNEL)

directories:
	mkdir -p ./sysroot/boot/grub

image: $(KERNEL) directories
	cp /usr/lib/grub/x86_64-pc/stage2_eltorito ./sysroot/boot/grub/stage2_eltorito
	bash ./image.sh
	cp $(KERNEL) ./sysroot/boot/kernel.elf
	sudo genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ./bootable.iso ./sysroot

run:
	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libXpm.so bochs -f bochsrc.txt

%.o: %.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@
