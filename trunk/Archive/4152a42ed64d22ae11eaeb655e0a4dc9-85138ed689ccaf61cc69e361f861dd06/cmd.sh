run() { g++ -o test -std=c++11 -DTHROW_SPEC="$1" -O3 main.cpp && echo "size: $(wc -c test)"; ./test ; echo "";  } ; for i in `seq 3` ; do echo iteration $i ; run '/**/' ; run 'throw()' ; run 'noexcept' ; done