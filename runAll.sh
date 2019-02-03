#!/usr/bin/env bash

for file in $(find test -type f | grep --invert-match '/lexical/'); do
  printf '━%.0s' $(seq 1 $(tput cols))
  echo ""
  #len=${#file}
  #echo "${len}"
  echo "cpsl < ${file}"
  ./cpsl < $file
  echo ""
  echo ""
done
