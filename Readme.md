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
    picotool \
    minicom
```
Get the sdk:
```sh
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
```

Get picotool: 
```sh
git clone https://github.com/raspberrypi/picotool.git
cd picotool
cmake -S . -B build -G Ninja \
  -DPICO_SDK_PATH=../../pico-sdk
cmake --build build
sudo cmake --install build
cd ..
picotool version
```

Build CMake config: `cmake -S . -B build -G Ninja`.
This should be done every time you change cmake config or change board.

Then compile: `cmake --build build --target flash`
Run `minicom -D <port> -b 115200` to get logs.
`<port>` should be something like `/dev/ttyACM0`.
To close minicom connection, press `Ctrl+A` then `x` then `enter`.