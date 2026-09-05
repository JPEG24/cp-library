#!/bin/bash

BLUE='\033[34m'
GREEN='\033[32m'
RED='\033[31m'
RESET='\033[0m'

trap 'echo; echo -e "[${BLUE}INFO${RESET}] stopped"; exit 130' INT

cnt=0

while true; do
  ((cnt++))

  ./random_test/gen > random_test/in.txt || exit 1

  timeout 2s ./a.out \
    < random_test/in.txt \
    > random_test/out1.txt
  status1=$?

  timeout 2s ./random_test/naive \
    < random_test/in.txt \
    > random_test/out2.txt
  status2=$?

  if [ $status1 -eq 124 ]; then
    echo
    echo
    echo -e "[${RED}FAILURE${RESET}] ${RED}TLE${RESET}"
    echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

    echo
    echo "input:"
    cat random_test/in.txt

    echo
    echo "output:"
    cat random_test/out1.txt

    exit 1
  fi

  if [ $status2 -eq 124 ]; then
    echo
    echo
    echo -e "[${RED}FAILURE${RESET}] naive.cpp ${RED}TLE${RESET}"
    echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

    echo
    echo "input:"
    cat random_test/in.txt

    echo
    echo "expected:"
    cat random_test/out2.txt

    exit 1
  fi

  if [ $status1 -ne 0 ]; then
    echo
    echo
    echo -e "[${RED}FAILURE${RESET}] ${RED}RE${RESET}"
    echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

    echo
    echo "input:"
    cat random_test/in.txt

    echo
    echo "output:"
    cat random_test/out1.txt

    exit 1
  fi

  if [ $status2 -ne 0 ]; then
    echo
    echo
    echo -e "[${RED}FAILURE${RESET}] naive.cpp ${RED}RE${RESET}"
    echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

    echo
    echo "input:"
    cat random_test/in.txt

    echo
    echo "expected:"
    cat random_test/out2.txt

    exit 1
  fi

  if diff -q \
    random_test/out1.txt \
    random_test/out2.txt \
    >/dev/null
  then
    printf "\r[${GREEN}SUCCESS${RESET}] %d AC" "$cnt"
    continue
  fi

  echo
  echo
  echo -e "[${RED}FAILURE${RESET}] ${RED}WA${RESET}"
  echo -e "[${BLUE}INFO${RESET}] case #${cnt}"

  echo
  echo "input:"
  cat random_test/in.txt

  echo
  echo "output:"
  cat random_test/out1.txt

  echo
  echo "expected:"
  cat random_test/out2.txt

  echo
  echo -e "[${RED}FAILURE${RESET}] test ${RED}failed${RESET} after $((cnt - 1)) AC"

  exit 1
done