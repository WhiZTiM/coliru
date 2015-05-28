#include <iostream>
#include <string>
#include <vector>
#include <map>


    struct some_key
    {
        int a = 0;
        double b = 0;
        std::string c;
        std::vector<int> d;

        bool operator<(some_key const& rhs) const
        {
            return std::tie(a,b,c,d)<std::tie(rhs.a,rhs.b,rhs.c,rhs.d);
        }
    };

    int main()
    {
        some_key key1;
        some_key key2;
        key2.a=1;
        
        std::map<some_key, std::string> m;
        m[key1] = "hi";
        m[key2] = "goodbye";

        std::cout<<m[key1]<<std::endl;
    }
