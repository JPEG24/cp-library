trap 'echo; echo "stopped"; exit 130' INT

cnt=0
while true; do
  ((cnt++))
  ./random_test/gen > random_test/in.txt
  timeout 2s ./a.out < random_test/in.txt > random_test/out1.txt
  timeout 2s ./random_test/naive < random_test/in.txt > random_test/out2.txt

  if ! diff random_test/out1.txt random_test/out2.txt; then
    echo "found ${cnt}"
    break
  else
    echo "match ${cnt}"
  fi
done