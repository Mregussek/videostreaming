#!usr/bin/env python
# Written by Mateusz Rzeczyca

import subprocess
import os
from sys import argv


def receive():
    os.system('/bin/nc -l 3305 | /sbin/mplayer -fps 31 - cache 1024')


def stream():
    subprocess.call('/sbin/raspivid -t 9999 -o - | /bin/nc 10.42.0.1 3305')


def choose(choice):
    if choice == 1:
        stream()
    elif choice == 2:
        receive()
    else:
        exit(0)


variable = argv[1]
choose(variable)
