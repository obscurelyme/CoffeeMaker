#!/bin/sh

numErrors=$(cat ./reports/cppcheck.xml | grep "<error" | wc -l)

if [ $numErrors -gt 0 ]
then
  echo "CppCheck found some errors with the source code. Please review the generated xml file in the artifacts for more information."
  exit 0
else
  echo "No issues detected!"
  exit 0
fi
