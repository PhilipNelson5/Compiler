#!/usr/bin/env bash
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

file=$(find test -type f | grep --invert-match '/lexical/' | grep $1 | head -n 1)
echo $file
printf '━%.0s' $(seq 1 $(tput cols))
echo ""

cat -n $file
echo ""

printf '━%.0s' $(seq 1 $(tput cols))
echo ""

output=$(./cpsl < ${file} 2>&1)

if [[ -z ${output} ]]; then
  echo -e "$GREEN[ PASS ]$RESET cpsl < ${file}"
else
  echo -e "$RED[ FAIL ]$RESET cpsl < ${file}"
  echo "${output}"
fi

echo ""
