cat>input.json<<JSON; clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lboost_system && ./a.out input.json
{
    "level": "should",
    "description": "very well performance wise",
    "label": "goperf",
    "children": [
	{"level":"should", "description":"be listening to spaces as well","label":"lisspace"},
	{"level":"will", "description":"a lot of levels back down again", "children":[
		{"level":"empty", "description":"empty","label":"empty", "children":[
			{"level":"can", "description":"skip all the way back here","label":"skiphere"},
			{"level":"can", "description":"take three linestr","label":"threelines"}
		]}
	]}
]}
JSON