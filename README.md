# VideoStreaming

## Getting Started
This is video streaming app written for Raspberry Pi.

Of course you can use this app to work with another WebCam, other than RPi.

Package for getting frames is OpenCV so it should work correctly only when you have it installed.

## Prepare RPi
I used Raspbian Stretch Lite to test this apps. In rpi_conf directory you can find files, which you should put in your RPi. ***ssh*** file enables connection through 22 port and ***wpa_supplicant.conf*** allows you to connect RPi to WiFi.

### Raspbian Install

Firstly you have to download Raspbian, my proposal is to choose Lite version.

[Download](https://www.raspberrypi.org/downloads/raspbian/)

Afterwards we have to find SD card, where the system will be. Best choice will be more than 8GB. I tested 8 and 16, memory is fine. On Linux you can find card by this command:

```bash
sudo fdisk -l
```

It will list all devices which are connected. For it always was ***/dev/sdc/***. Next umount disc, if it gives an error like it isn't mount, that's fine, don't worry.

```bash
sudo umount /dev/sdc
```

The last point is to copy .img file to SD card. You can use this:

```bash
sudo dd bs=1M if=rasbian.img of=/dev/sdc
```

Of course replace raspbian.img to path to the correct img file of raspbian, which you have already downloaded. Insert the card to Raspberry Pi and chech if everything works. When yes, go to next point.

### Configure Raspbian

Put SD card to your computer again, hopefully you will see 2 cards connected named ***boot*** and ***root***. Only what you have to do is to copy ***ssh*** and ***wpa_supplicant.conf*** to ***boot*** directory. Don't forget about setting correctly wpa_supplicant in case of right WiFi connection.

## Author
Mateusz Rzeczyca

Student - AGH University of Science and Technology

info@mateuszrzeczyca.pl

Cracow, Poland

04.01.2019

## License
This project is licensed under the GNU GPL3 License - see the LICENSE.md file for details