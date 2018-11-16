#!/bin/bash

# Testing camera streaming with tools from raspbian
# Made by Mateusz Rzeczyca.

# choose the right interface
dev=wlan0 # WLAN / WiFi
# dev=eth0  # Ethernet

# get the IP address
getaddr=/sbin/ifconfig
addr=`$getaddr $dev | grep "inet addr" | cut -d ':' -f 2 | cut -d ' ' -f 1`

# stream video using raspivid and send using netcat
netcat=/bin/nc
streamcam=/sbin/raspivid
$streamcam -t 999999 -o - | $netcat $addr 3305
