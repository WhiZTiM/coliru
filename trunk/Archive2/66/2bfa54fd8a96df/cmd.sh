clang++ --version && clang++ -c -fPIC main.cpp -o main.o && gcc -shared -o libmain.so main.o && nm -DC libmain.so