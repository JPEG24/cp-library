#!/bin/bash

BLUE='\033[34m'
GREEN='\033[32m'
RED='\033[31m'
RESET='\033[0m'

rm -rf interactive
mkdir interactive
mkfifo interactive/pipe

trap 'rm -f interactive/pipe; echo; echo -e "[${BLUE}INFO${RESET}] stopped"; exit 130' INT

cnt=0

while true; do
  ((cnt++))

  timeout 4s pypy3 main.py < interactive/pipe \
    | tee interactive/out.txt \
    | pypy3 judge.py \
    | tee interactive/judge.txt > interactive/pipe

  st=("${PIPESTATUS[@]}")

  if [ ${st[0]} -ne 0 ]; then
    echo
    echo
    echo -e "[${RED}FAILURE${RESET}] ${RED}WA/TLE/RE${RESET}"
    echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

    echo
    echo "output:"
    cat interactive/out.txt

    echo
    echo "judge:"
    cat interactive/judge.txt

    rm -f interactive/pipe
    exit 1
  fi

  if [ ${st[2]} -ne 0 ]; then
    echo
    echo
    echo -e "[${RED}FAILURE${RESET}] judge ${RED}RE${RESET}"
    echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

    echo
    echo "output:"
    cat interactive/out.txt

    echo
    echo "judge:"
    cat interactive/judge.txt

    rm -f interactive/pipe
    exit 1
  fi

  printf "\r[${GREEN}SUCCESS${RESET}] %d AC" "$cnt"
done

rm -f interactive/pipe