#!/bin/sh

mkdir release &&
  cp ./build/main ./release/ultra-cosmo-invaders &&
  tar vcfz /tmp/ultra-cosmo-invaders-linux.tar.gz ./release
