#!/bin/sh

numErrors=$(cat ./check.xml | grep "<error" | wc -l)

if [ $numErrors -gt 0 ]
then
  exit 1
else
  exit 0
fi
