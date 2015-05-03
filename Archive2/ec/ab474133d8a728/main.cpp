
#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

typedef int Score;

typedef pair<Score,Score> Result;

ostream& operator<<(ostream& o, const Result& r)
{
    o << "{" << r.first << "-" << r.second << "}" ;
    return o;
}

struct Match
{
    string p[2];
    Score s[2];
    
    bool has(string p1, string p2)
    {
        if( (p1==p[0]) && (p2==p[1]) ) return true;
        if( (p1==p[1]) && (p2==p[0]) ) return true;
        return false;
    }
    Result result(string p1, string p2)
    {
        if( (p1==p[0]) && (p2==p[1]) ) return make_pair(s[0],s[1]);
        if( (p1==p[1]) && (p2==p[0]) ) return make_pair(s[1],s[0]);
        throw "error";
    }
};

struct Tournament : vector<Match>
{
    bool played(string p1, string p2)
    {
        for(size_t i=0;i<size();++i)
            if( at(i).has(p1,p2) )
                return true;
        return false;
    }
    Result result(string p1, string p2)
    {
        for(size_t i=0;i<size();++i)
            if( at(i).has(p1,p2) )
                return at(i).result(p1,p2);
        throw "error";
    }
};

int main()
{
    Tournament t;
    
    t.push_back( Match{ {"john", "dan"}, { 3, 7} } );
    
    cout << t.result("dan","john") << endl;  
}

