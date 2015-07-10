clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lpython2.7 -shared -fPIC -o mymodule.so
python2.7 << EOF
import mymodule
import sys
assert(42 == mymodule.run_mymodule("a", "bc", "def", 1))
assert(42 == mymodule.run_mymodule("a", "bc", "def", None))
assert(42 == mymodule.run_mymodule("a", "bc", "def", lambda x: x))
assert(42 == mymodule.run_mymodule("a", "bc", "def", "ghij"))
assert(42 == mymodule.run_mymodule("a", "bc", "def", sys))
EOF
echo $?