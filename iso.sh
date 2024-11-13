#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos2.kernel isodir/boot/myos2.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "myos2" {
	multiboot /boot/myos2.kernel
}
EOF
grub2-mkrescue -o myos2.iso isodir
