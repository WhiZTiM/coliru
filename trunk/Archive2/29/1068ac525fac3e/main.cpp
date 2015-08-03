#include <map>
#include <iostream>
#include <typeinfo>
using namespace std;

int main(){

    map<string, map<int, int> > outer_map;
    auto inner_map = outer_map["outer_key"]; //should insert a key of "outer_key" into the map with a value of a default initialized map<int,int>
    inner_map.insert(pair<int, int>(1,2));

    cout << outer_map.find("outer_key")->second[1]; //print out the inner map's only value.  Should be 2.
}