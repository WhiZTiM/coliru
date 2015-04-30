#include <iostream>
#include <string>
#include <map>
using namespace std;

void print(const map<char, pair<int,int>* >& refers) {
    for (auto const &i : refers) {
        cout << i.second->first << ',' << i.second->second << '\n';
    }
}

int main() {
    map<char, pair<int,int> > mapa = {{'a', {1,2}},{'c', {2,3}}};
    map<char, pair<int,int>* > refers;

    for (auto &i : mapa) {
        refers.insert({i.first, &(i.second)});            
    }
    
    cout << "ABANS\n";
    print(refers);
    mapa.insert({'b', {0,0}});
    cout << "DESPRES INS\n";
    print(refers);
    mapa.erase('b');
    cout << "DESPRES ERASE\n";
    print(refers);
}
