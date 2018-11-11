#!/bin/bash

sudo apt-get install mplayer nc

nc -l 3305 | mplayer -fps 31 -cache 1024 -
