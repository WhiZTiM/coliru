clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
class GoodDerived(example.Base):
    def __init__(self):
        example.Base.__init__(self)

class BadDerived(example.Base):
    def __init__(self):
        pass

assert(isinstance(GoodDerived(), example.Base))
assert(isinstance(BadDerived(), example.Base))
try:
    example.foo(GoodDerived())
    got_exception = False
except:
    got_exception = True
finally:
    assert(not got_exception)

try:
    example.foo(BadDerived())
    got_exception = False
except:
    got_exception = True
finally:
    assert(got_exception) 
EOF
echo $?