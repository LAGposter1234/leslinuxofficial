#!/bin/bash
set -e
cd initramfs
gcc -static -o init init.c -Iusr/include -nostartfiles -nostdlib -fno-stack-protector
#cp arch/x86/boot/bzImage ./boot/kernel

find . | cpio -H newc -o | gzip > ../initramfs.img
cd ..
qemu-system-x86_64 -kernel initramfs/boot/kernel -initrd initramfs.img -append "console=tty0 loglevel=0" -drive file=persist.img,format=raw -device virtio-gpu -device qemu-xhci -device usb-tablet -m 2G
