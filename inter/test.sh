trap 'echo; echo "stopped"; exit 130' INT

g++ ../main.cpp -o ../a.out
g++ judge.cpp -o io/judge

cnt=0
while true; do
  ((cnt++))
  timeout 2s oj t/r \
    -c "../a.out" \
    "io/judge" \
    > io/log.txt 2>&1

  status=$?

  if [ $status -ne 0 ]; then
    echo "found"
    break
  fi

  echo "match ${cnt}"
done