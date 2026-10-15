rm -rf interactive
mkdir interactive

g++ main.cpp -o a.out || exit 1
g++ judge.cpp -o interactive/judge || exit 1