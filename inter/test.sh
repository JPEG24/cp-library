trap 'rm -f io/pipe; echo; echo stopped; exit 130' INT

g++ ../main.cpp -o ../a.out || exit 1
g++ judge.cpp -o io/judge || exit 1

rm -f io/pipe
mkfifo io/pipe

cnt=0
while true; do
  ((cnt++))

  ../a.out < io/pipe \
    | tee io/out.txt \
    | ./io/judge \
    | tee io/judge.txt > io/pipe

  st=("${PIPESTATUS[@]}")

  if [ ${st[0]} -ne 0 ] || [ ${st[2]} -ne 0 ]; then
    echo "wrong $cnt"
    echo "a.out  : ${st[0]}"
    echo "judge  : ${st[2]}"
    break
  fi

  echo "correct $cnt"
done

rm -f io/pipe