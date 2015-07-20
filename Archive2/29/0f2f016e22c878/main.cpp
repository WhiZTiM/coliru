#include <iostream>
#include <set>
#include <utility>

using namespace std;

template<typename T, typename U>
inline ostream& operator<<(ostream& os, const pair<T,U> &p){
    os<<"("<<p.first<<","<<p.second<<")";
    return os;
}


template<typename T>
inline ostream& operator<<(ostream& os, const set<T> &s){
    os<<"{";
    for(auto it = s.begin() ; it != s.end() ; it++){
        if(it != s.begin())
            os<<",";
        os<<*it;
    }
    os<<"}";
    return os;
}

int main()
{
    set<pair<int,int>> s {{1,2}};
    cout<<s<<endl;
}