clang++ main.cpp
echo "Program input: no input"
./a.out
for input in "xxx" "--a" "--a--b--"; do echo; echo Program input: $input; ./a.out <<< $input; done