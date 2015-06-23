base64 -d main.cpp > main.zip
unzip main.zip
cd duk*
make -f Makefile.cmdline
./duk -e 'print("Hello, JS!")'