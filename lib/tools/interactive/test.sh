trap 'rm -f interactive/pipe; echo; echo stopped; exit 130' INT

rm -f interactive/pipe
mkfifo interactive/pipe

cnt=0
while true; do
  ((cnt++))

  ./a.out < interactive/pipe \
    | tee interactive/out.txt \
    | ./interactive/judge \
    | tee interactive/judge.txt > interactive/pipe

  st=("${PIPESTATUS[@]}")

  if [ ${st[0]} -ne 0 ] || [ ${st[2]} -ne 0 ]; then
    echo "wrong $cnt"
    echo "a.out  : ${st[0]}"
    echo "judge  : ${st[2]}"
    break
  fi

  echo "correct $cnt"
done

rm -f interactive/pipe