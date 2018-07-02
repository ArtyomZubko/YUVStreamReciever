#!/bin/bash
sudo modprobe bcm2835-v4l2
sudo v4l2-ctl --set-fmt-video=width=620,height=480,pixelformat=0

hostname="$1"
hostport="$2"
yellow="\033[33m"
red="\033[31m"

if ["$hostname" = ""]
then
echo -en "${red}Empty hostname \n"
exit
fi

echo -en "${yellow}Streaming to ${hostname}:${hostport} started \n"
sudo cat /dev/video0 | netcat -u ${hostname} ${hostport}
echo -en "${yellow}Streaming stopped \n"
