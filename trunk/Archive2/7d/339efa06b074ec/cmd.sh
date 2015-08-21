#title Triviality checker
g++ -std=c++11 -E main.cpp -o  output.cpp ; astyle -q output.cpp | perl -pe 's,template,\ntemplate,g'
g++ -std=c++11 -c -S output.cpp -o - | c++filt | grep 'call' | grep -v ___ | grep -v 'initialization' | sed -e 's,_, ,g' | sed -e 's,call	int,,g; s,<[ABCD]\, ,,g; s,[<>()],,g' | sed -e  's,ble,ble: ,g'