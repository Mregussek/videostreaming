# Tutorial for RPi cross compiling (Hello World)

There is one file named **helloworld.cpp** which prints simple Hello World. Before reading my recommendation is to go through [Wikipedia page](https://en.wikipedia.org/wiki/Cross_compiler) about cross compilation.

We know that compiling on RPi can take some time. Better is to take all the benefits from our main machine to build stuff.

Firstly we need to install cross compiler by this commands:

```bash
sudo apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi

sudo apt-get install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
```

To understand what we are going to do it is good to check

```bash
arm-linux-gnueabi-g++ --target-help
```

At the moment we should discover -march option which will be important for correct compilation.

Next you can check your RPi's architecture by

```bash
uname -a

example: Linux raspberrypi 4.14.98+ #1200 Tue Feb 12 20:11:02 GMT 2019 armv6l GNU/Linux
```

Now we know, that we are goona build for armv6!

Also you can check if you have armel or armhf:

```bash
readelf -A /proc/self/exe | grep Tag_ABI_VFP_args

example:  Tag_ABI_VFP_args: VFP registers
```

Output means my RPi has armhf architecture. This is why we should use arm-linux-gnueabihf-g++ cross compiler but I have no reason why it returns error during compilation. I will find out what is wrong asap.

```bash
/usr/arm-linux-gnueabihf/include/c++/7/bits/exception.h:63:39: sorry, unimplemented: Thumb-1 hard-float VFP ABI
     exception() _GLIBCXX_USE_NOEXCEPT { }
```

Then I decided to change to arm-linux-gnueabi-g++ and it worked!

```bash
arm-linux-gnueabi-g++ helloworld.cpp -o hw_cross -march=armv6
```

Then send to RPi using rsync:

```bash
rsync -azv ./hw_cross pi@<your_rpi_ip>:~/
```

and run it!

```bash
./hw_cross

example:
pi@raspberrypi:~ $ ./hw_cross
Hello World
```

## Author

Mateusz Rzeczyca

Student - AGH University of Science and Technology

info@mateuszrzeczyca.pl

Cracow, Poland

07.04.2019
