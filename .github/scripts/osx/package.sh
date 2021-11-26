#!/bin/sh

mkdir release &&
  cp ./build/main ./release/ultra-cosmo-invaders &&
  tar vcfz ultra-cosmo-invaders-osx.tar.gz ./release
