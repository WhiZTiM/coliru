#title GCC Calling conventions (parameter passing)
g++ -c -std=c++14 -O1 -Wall -pedantic main.cpp -S -masm=intel -o - | c++filt | grep -v '\.' | perl -pe 's,(	call.*),\1\n,g; s,main:,\nmain:,g; s,impl_test,\nimpl_test,g'
#title Clang Calling conventions (parameter passing)
clang++ -c -std=c++14 -O2 -Wall -pedantic main.cpp -S -masm=intel -o - | c++filt | grep -v '\.' | perl -pe 's,(	call.*),\1\n,g; s,main:,\nmain:,g; s,impl_test,\nimpl_test,g'