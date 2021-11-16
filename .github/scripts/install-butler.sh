#!/bin/bash

curl -L -o butler.zip https://broth.itch.ovh/butler/linux-amd64/LATEST/archive/default &&
  unzip butler.zip &&
  chmod +x butler &&
  ./butler -V
