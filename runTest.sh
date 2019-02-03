#!/usr/bin/env bash

file=$(find test -type f | grep --invert-match '/lexical/' | grep $1 | head -n 1)
echo $file
printf '━%.0s' $(seq 1 $(tput cols))
cat -n $file
printf '━%.0s' $(seq 1 $(tput cols))
echo "cpsl < ${file}"
echo ""
./cpsl < $file
