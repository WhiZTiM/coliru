g++ -I /usr/include/python2.7 -fpic -pedantic -Wall -std=c++11 -c -o example.o main.cpp
g++ -o example.so -shared example.o -lboost_python -lpython2.7
python << EOF
import example
print "test"
def callback_function():
    print 'button has been pressed'
o = example.GuiButton()
o.on_pressed = callback_function
o.on_pressed()
EOF