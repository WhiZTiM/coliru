cat>tzdb.csv<<TZDB; g++ -std=c++11 -O0 -Wall -pthread -pedantic main.cpp -lboost_system && ./a.out
"ID","STD ABBR","STD NAME","DST ABBR","DST NAME","GMT offset","DST adjustment","DST Start Date rule","Start time","DST End date rule","End time"
"America/New_York","EST","Eastern Standard Time","EDT","Eastern Daylight Time","-05:00:00","+01:00:00","2;0;3","+02:00:00","1;0;11","+02:00:00"
"Asia/Hong_Kong","HKT","HKT","","","+08:00:00","+00:00:00","","","","+00:00:00"
TZDB