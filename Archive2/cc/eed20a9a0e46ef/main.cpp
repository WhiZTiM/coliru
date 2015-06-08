//Title of this code
//Rextester.Program.Main is the entry point for your code. Don't change it.
//Compiler version 4.0.30319.17929 for Microsoft (R) .NET Framework 4.5

#include <vector>
#include <iostream>
#include  <algorithm>


using namespace std;

        void PlaceArrayData(vector<int> const&  source)
        {
            auto maxelem = std::max_element(source.begin(), source.end());
            int minsize = max<int>(source.size(), *maxelem);
            vector<int> target (minsize);
    	   
            int evenindex = 1, oddindex = 0;
            
            for( auto val : source)
            {
                if (val % 2 == 0)
                {
                    target[evenindex] = val;
                    evenindex += 2;
                }
                else 
                {
                    target[oddindex]  = val;
                    oddindex += 2;
                }
            }
            
            for(auto val : target)
            {
                cout << val << ",";
            }
            cout << "\n";
        }
        
        
        
        
        int main()
        {
            PlaceArrayData({1,2,3,4});
            PlaceArrayData({1,3,4});
            PlaceArrayData({2,4});
        }
    
