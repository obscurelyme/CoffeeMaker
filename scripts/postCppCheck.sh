#!/bin/sh

numErrors=$(cat ./check.xml | grep "<error" | wc -l)

if [ $numErrors -gt 0 ]
then
  echo "There were errors detected in the generated XML file. Please review check.xml in the artifacts for more information."
  exit 1
else
  echo "No issues detected!"
  exit 0
fi
