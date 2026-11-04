# Pico light station

## Getting started
Install prerequisite:
```sh
sudo apt update
sudo apt upgrade
sudo apt install -y \
    cmake \
    ninja-build \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    build-essential \
    pkg-config \
    libusb-1.0-0-dev \
    minicom
```
Get the sdk:
```sh
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
```
Build CMake config: `cmake -S . -B build -G Ninja`.
This should be done every time you change cmake config or change board.

Then compile: `cmake --build build`
Copy the uf2 file on the Pico and run `minicom -D <port> -b 115200` to get logs.
`<port>` should be something like `/dev/ttyACM0`.