#!/bin/sh

if [[ -d ./licensed-assets ]]; then
  echo "Packaging licensed assets..." &&
    mkdir release &&
    cp ./build/main ./release/ultra-cosmo-invaders &&
    cp -r ./assets ./release/assets &&
    cp ./licensed-assets/images/*.png ./release/assets/images &&
    tar vcfz ultra-cosmo-invaders-osx.tar.gz ./release
else
  echo "Licensed assets will NOT be packaged..." &&
    mkdir release &&
    cp ./build/main ./release/ultra-cosmo-invaders &&
    cp -r ./assets ./release/assets &&
    tar vcfz ultra-cosmo-invaders-osx.tar.gz ./release
fi
