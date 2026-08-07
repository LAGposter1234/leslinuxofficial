#!/bin/bash
echo "WARNING: This will wipe the contents of drive sda, which is currently mounted at home."
echo "Exit now if this is not what you intend, or have unfinished bisuniess."

printf "Press any key to continue...\n"
read -r -n 1 -s

echo "Unmount drive..."

umount /home

echo "Installing..."

mkfs.ext4 /dev/sda 

mount /dev/sda /mnt

cp -a /bin /mnt/
cp -a /lib /mnt/
cp -a /lib64 /mnt/
cp -a /usr /mnt/
cp -a /boot /mnt/
cp -a /etc /mnt/

mkdir -p /mnt/{dev,proc,sys,tmp,home}
chmod 1777 /mnt/tmp

cp -a /root /mnt/

rm /mnt/init
tcc -static -nostdlib /initi.c -o /mnt/bin/init
chmod +x /mnt/init

mkdir -p /mnt/boot/grub
grub-install --force --target=i386-pc --recheck --root-directory=/mnt /dev/sda

rm /mnt/bin/lesinstall.sh

umount /mnt