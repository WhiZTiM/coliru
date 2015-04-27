clang++ -std=c++11 -Os -Wall -pthread -pedantic main.cpp -lboost_regex && ./a.out <<DOT
digraph G {
  rankdir=LR
  I [label="", style=invis, width=0]
  I -> 0
  0 [label="0", peripheries=2]
  0 -> 0 [label="a"]
  0 -> 1 [label="!a"]
  1 [label="1"]
  1 -> 0 [label="a"]
  1 -> 1 [label="!a"]
}
DOT