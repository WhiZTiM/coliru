clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lpython2.7 -shared -fPIC -o mymodule.so
python2.7 << EOF
import mymodule
assert(42 == mymodule.run_mymodule("a", "bc", "def", 1))
EOF
echo $?