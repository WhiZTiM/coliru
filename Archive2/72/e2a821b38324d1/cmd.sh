cp -r /usr/local/bin/Wide/WideLibrary .
wide --include="/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/../../../../include/c++/4.8.2" --include="/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/../../../../include/c++/4.8.2/x86_64-unknown-linux-gnu/" --include="/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/../../../../include/c++/4.8.2/backward" --include="/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include" --include="/usr/local/include" --include="/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include-fixed" --include="/usr/include/x86_64-linux-gnu" --include="/usr/include" main.cpp && g++ a.o && ./a.out