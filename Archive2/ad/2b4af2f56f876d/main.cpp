#include <map>
#include <sstream>
#include <ostream>
#include <iostream>
#include <iterator>
#include <stdint.h>
#include <unordered_set>

namespace unorderedHelpers {
    
    template<typename UnorderedIn1, typename UnorderedIn2, 
             typename UnorderedOut = UnorderedIn1>
    UnorderedOut make_intersection(const  UnorderedIn1 &in1, const  UnorderedIn2 &in2)
    {   
        if (in2.size() < in1.size()) {
        	return make_intersection(in2, in1);
        }
        
        UnorderedOut out;
        auto e = in2.end();
        for(auto & v : in1)
        {
        	if (in2.find(v) != e){
        		out.insert(v);
        	}
        }
        return out;
    }
    
    template<typename UnorderedIn1, typename UnorderedIn2, 
             typename UnorderedOut = UnorderedIn1>
    UnorderedOut make_union(const UnorderedIn1 &in1, const UnorderedIn1 &in2)
    {
        UnorderedOut out;
        out.insert(in1.begin(), in1.end());
        out.insert(in2.begin(), in2.end());
        return out;
    }
    
}


int main()
{
    
   std::unordered_set<int> a{1,2,3,0};
   std::unordered_set<int> b{3,4,1,2,7};
   auto c = unorderedHelpers::make_intersection(a,b);
   
   std::copy(c.begin(),c.end(),std::ostream_iterator<int>(std::cout,","));
   
}