#title TaskQueue allocator_arg, packaged_task, allocate_shared and dispatch/post/post+callback.
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic -Wno-enum-compare -pthread main.cpp -ltbb && ./a.out