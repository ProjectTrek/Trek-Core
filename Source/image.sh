cat << EOF > ./sysroot/boot/grub/menu.lst
default 0
title trek-os
kernel /boot/kernel.elf
EOF
