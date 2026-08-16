trap 'echo; echo "stopped"; exit 130' INT

g++ gen.cpp -o io/gen
g++ ../main.cpp -o ../a.out
g++ naive.cpp -o io/naive

cnt=0
while true; do
  ((cnt++))
  io/gen > in.txt
  timeout 2s ../a.out < in.txt > out1.txt
  timeout 2s io/naive < in.txt > out2.txt

  if ! diff out1.txt out2.txt; then
    echo "found"
    break
  else
    echo "match ${cnt}"
  fi
done