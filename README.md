# RPI-CEC
Manage Rasperry PI CEC commands from C++

To compile this program install the following packages:

apt install libcec
apt install libcec4-dev
apt install g++
apt install raspberrypi-bootloader
apt install libraspberrypi-dev

the command to compile the program is included into the build.sh file.

The libcec interface is not stable and may change in time. Every time it is updated it can broke the compilation, and the code must be updated accordingly.

This project took heavy inspiration from this one: https://github.com/DrGeoff/cec_simplest
