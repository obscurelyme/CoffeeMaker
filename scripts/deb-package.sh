#!/bin/sh

cp ./build/main ./resources/linux/ultracosmoinvaders/usr/share/ultracosmoinvaders/ultracosmoinvaders &&
cp -r ./build/assets ./resources/linux/ultracosmoinvaders/usr/share/ultracosmoinvaders/ &&
dpkg-deb --build ./resources/linux/ultracosmoinvaders
