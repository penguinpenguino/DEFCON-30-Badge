# DEFCON-30-Badge

Tool for writing custom badge firmware. Only supports buttons, screen and LEDs right now. Nothing in place for the speaker or keyboard.

Also this was just a quick write thing so if you have any complaints, bottle it up.

## Setup

1. Clone [pico-sdk](https://github.com/raspberrypi/pico-sdk)
2. Copy `./pico-sdk/external/pico_sdk_init.cmake` to `./pico_sdk_init.cmake`
3. Install dependencies `sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib`


## Building

```sh
mkdir build
cd build
cmake .. -DPICO_SDK_PATH=../pico-sdk
make
```
