g++ -E main.cpp | tail -n 35 | grep -v ^\# > output.cpp ; cat output.cpp