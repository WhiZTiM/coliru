ln -s main.cpp execlib.c && \
    gcc -shared -fPIC -olibexeclib.so -Wl,-e,start execlib.c && \
    ./libexeclib.so