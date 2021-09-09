#!/usr/bin/env bash

portenta_h7_rules () {
    echo ""
    echo "# Portenta H7 bootloader mode UDEV rules"
    echo ""
cat <<EOF
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
EOF
}

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

portenta_h7_rules > /etc/udev/rules.d/49-portenta_h7.rules

# reload udev rules
echo "Reload rules..."
udevadm trigger
udevadm control --reload-rules
