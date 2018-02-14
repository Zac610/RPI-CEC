#!/bin/bash

#setterm --blank 0 --powersave off --cursor off

CEC_RED=114
CEC_GREEN=115
CEC_YELLOW=116
CEC_BLUE=113

#while :
#do

clear

echo
echo RPI-CEC Menu
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo
echo -e "\e[7;49;31mLaunch Kodi\e[0m"

./rpi-cec
if [ "$?" -eq "$CEC_RED" ]; then
   /DietPi/dietpi/misc/start_kodi
fi

#done