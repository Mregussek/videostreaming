# Tutorial for RPi cross compiling with cmake (Hello World)

As we know from the previous tutorial our architecture is armv6. My plan is to use cmake to make cross-compiled binary file which will be able to be run on the RPi.

We can start with creating our **CMakeLists.txt** file. 

```bash
cmake_minimum_required(VERSION 3.6)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)
set(CMAKE_ASM_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_SYSTEM_PROCESSOR arm)

add_definitions("-march=armv6")

set(COMPILE_DEFINITIONS -Werror -Wall)

add_executable(hw_cmake helloworld.cpp)
```
I will explain every line of this cmake file. Here we are defining arm architecture and compilers which we're gonna use. I think this is quite understandable. As we know from the late tutorial now I cannot understand why *arm-linux-gnueabi-gcc* and *arm-linux-gnueabihf-gcc* not.

```bash
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)
set(CMAKE_ASM_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_SYSTEM_PROCESSOR arm)
```

As this line says we add definition to compilation. This is done by the same way when we wrote compilation command in terminal.

```bash
add_definitions("-march=armv6")
```

Also it is important to let cmake know that it should build binary file. Cmake knows which file will executable by this line:

```bash
add_executable(hw_cmake helloworld.cpp)
```

Now we are prepared! My proposal is to make build directory and then do all the work.

```bash
mkdir build
cd build
```

We should run cmake:

```bash
cmake /path/to/file

example: cmake ..
```

Check number of cores to build faster and then build it. 

```bash
nproc

example output: 8

make -j8
```

Now we are ready to send binary to the RPi thanks to for instance rsync:

```bash
rsync -azv ./hw_cmake pi@<your_pi_ip>:~/
```

Afterwards best plan is to connect through ssh and check if job is done.

```bash
ssh pi@<your_pi_ip>
password:

pi@raspberrypi:~ $ ls
hw_cmake  hw_cross
pi@raspberrypi:~ $ ./hw_cmake
Hello World
```

Work is a little bit complicated when our plan is to add arm_sysroot to cmake. I will find out what
to do asap!

## Author

Mateusz Rzeczyca

Student - AGH University of Science and Technology

info@mateuszrzeczyca.pl

Cracow, Poland

07.04.2019