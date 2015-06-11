#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;


int main()
{
    map<string,int> word_count;
    word_count.insert(make_pair("first",1));
    word_count.insert(make_pair("sceond",2));
    word_count.insert(make_pair("first",3));
    
    cout<<word_count["first"]<<endl;
    
   // for(auto x : word_count){
        //cout << x->first << " " << x->second <<endl;
        //count
    //}
    
    return 0;
}
