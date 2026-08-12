#!/bin/bash
echo "WARNING: This will wipe the contents of drive sda, which is currently mounted at home."
echo "Exit now if this is not what you intend, or have unfinished bisuniess."

printf "Press any key to continue...(except the power button)\n"
read -r -n 1 -s

# Get disks

drives=()

for dev in /sys/block/*; do
    name="${dev##*/}"

    case "$name" in
        loop*|ram*|zram*|dm-*)
            continue
            ;;
    esac

    drives+=("/dev/$name")
done

# Ask user which disk they want to install to

PS3="Select installation drive: "
select drive in "${drives[@]}"; do
    if [ -n "$drive" ]; then
        PS3="Are you sure you want to install to $drive? "
        select confirm in "Yes" "No"; do
            case "$confirm" in
                Yes)
                    break 2
                    ;;
                No)
                    break
                    ;;
            esac
        done
    fi
done

echo "Installing to drive $drive..."

mkfs.ext4 $drive

mount $drive /mnt

cp -a /bin /mnt/
cp -a /lib /mnt/
cp -a /lib64 /mnt/
cp -a /usr /mnt/
cp -a /boot /mnt/
cat > /mnt/boot/grub/grub.cfg <<EOF
timeout=5

menuentry 'LesLinux' {
    linux /boot/kernel root=$drive rw loglevel=1
}
EOF
cp -a /etc /mnt/

mkdir -p /mnt/{dev,proc,sys,tmp,home}
chmod 1777 /mnt/tmp

cp -a /root/. /mnt/

rm /mnt/init
tcc -static -nostdlib /initi.c -o /mnt/bin/init
chmod +x /mnt/init

mkdir -p /mnt/boot/grub
grub-install --force --target=i386-pc --recheck --root-directory=/mnt $drive

rm /mnt/bin/lesinstall.sh

umount /mnt
