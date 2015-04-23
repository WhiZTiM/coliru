g++ -std=c++11 -O2 -I /usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o Test.so
python2.7 <<HERE
from Test import *

class Bar(Base):
    def __init__(self):
        print 'Bar.__init__'

foo(Bar())

HERE