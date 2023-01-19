#!/usr/bin/env sh

echo "# Enable access to Fluigent instruments without superuser rights
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0000\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0001\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0002\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0003\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0010\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0012\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"04d8\", ATTRS{idProduct}==\"0017\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"0483\", ATTRS{idProduct}==\"000A\", MODE=\"0666\"
KERNEL==\"hidraw*\", ATTRS{idVendor}==\"0483\", ATTRS{idProduct}==\"000B\", MODE=\"0666\"
" > /etc/udev/rules.d/99-fluigent.rules
