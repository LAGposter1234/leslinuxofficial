#!/bin/bash
qemu-system-x86_64 -hda persist.img -device virtio-gpu -device qemu-xhci -device usb-tablet