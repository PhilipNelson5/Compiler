#!/usr/bin/env bash

file=$(find test -type f | grep --invert-match '/lexical/' | grep $1 | head -n 1)
echo $file
printf '━%.0s' $(seq 1 $(tput cols))
echo ""
cat -n $file
echo ""
printf '━%.0s' $(seq 1 $(tput cols))
echo ""
echo "cpsl < ${file}"
echo ""
./cpsl < $file
