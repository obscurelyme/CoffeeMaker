#!/bin/sh

Directory="build/assets"

if [ -d "$Directory" ]; then
  rm -rf "$Directory" && cp -r assets "$Directory"
else
  cp -r assets "$Directory"
fi
