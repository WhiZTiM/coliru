clang++ -std=libc++ -std=c++0x -lboost_log -lboost_chrono -lboost_log_setup -lboost_thread -lboost_system -DBOOST_LOG_DYN_LINK  -O3 -Wall -pedantic  -pthread main.cpp && ./a.out