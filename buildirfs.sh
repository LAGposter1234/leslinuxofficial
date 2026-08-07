#!/bin/bash
set -e
cd initramfs
gcc -static -o init init.c -Iusr/include -nostartfiles -nostdlib -fno-stack-protector
gcc -static -o bin/leslogin lesinit.c -Iusr/include -nostartfiles -nostdlib -fno-stack-protector
#cp arch/x86/boot/bzImage ./boot/kernel

find . | cpio -H newc -o | gzip > ../initramfs.img
cd ..
qemu-system-x86_64 -kernel arch/x86/boot/bzImage -initrd initramfs.img -append "console=tty0 quiet loglevel=3" -drive file=persist.img,format=raw -vga std -m 2G
