#!/bin/sh

##################################################################################
## This is the plethora of dependencies that Linux needs before SDL2 is compiled.#
## if they are NOT present at SDL2 compile time, the integration of SDL2 simply  #
## does not work, and there is quite little to go on.                            #
###################################################################################

sudo apt-get install -y build-essential git make cmake autoconf automake \
libtool pkg-config libasound2-dev libpulse-dev libaudio-dev libjack-dev \
libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev \
libxinerama-dev libxxf86vm-dev libxss-dev libgl1-mesa-dev libdbus-1-dev \
libudev-dev libgles2-mesa-dev libegl1-mesa-dev libibus-1.0-dev \
fcitx-libs-dev libsamplerate0-dev libsndio-dev libwayland-dev \
libxkbcommon-dev libdrm-dev libgbm-dev
