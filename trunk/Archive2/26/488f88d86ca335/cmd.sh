cat <<TRADE>trade.txt; cat <<NBBO>nbbo.txt; g++ -std=c++03 -Wall -pedantic main.cpp && ./a.out
MSFT 100 57.2 13:00
MSFT 100 58.2 13:10
GOOG 200 300.2 13:01
GOOG 300 300.2 14:30
TRADE
GOOG 100 300.2 100 300.3 13:03
GOOG 100 300.3 100 300.4 13:04
MSFT 100 57.2 100 57.3 12:09
MSFT 100 57.3 100 58.4 13:05
NBBO