rm -rf random_test
mkdir random_test

g++ gen.cpp -o random_test/gen || exit 1
g++ main.cpp -o a.out || exit 1
g++ naive.cpp -o random_test/naive || exit 1