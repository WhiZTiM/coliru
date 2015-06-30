clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
foo1 = example.Foo.get("abc")
foo2 = example.Foo.get("abc")
foo3 = example.Foo.get("def")
assert(foo1 == foo2)
assert(foo1 != foo3)
EOF
echo $?