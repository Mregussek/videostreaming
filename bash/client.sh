#!/bin/bash

# Testing camera streaming with tools from raspbian
# Made by Mateusz Rzeczyca.

# choose right interface
dev=wlan0 # WLAN / WiFi
#dev=eth0  # Ethernet

# get the IP address
getaddr=/sbin/ifconfig
addr=`$getaddr $dev | grep "inet addr" | cut -d ':' -f 2 | cut -d ' ' -f 1`

# get data from RPi using  netcat and see streamed video
netcat=/bin/nc
player=/sbin/mplayer
$netcat -l 3305 | $player -fps 31 -cache 1024
