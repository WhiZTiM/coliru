#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

// Tuple key search string (name~type).
typedef string pcuTupleSearchStrIdT;

// Map of Tuple containers, keyed on Tuple name/type.
typedef map<pcuTupleSearchStrIdT,
            int> pcuTupleStrSearchT;



bool findTuple(pcuTupleStrSearchT tupleList,std::string refEntityTag, int *tuple)
{
  pcuTupleStrSearchT::iterator tupleItr = tupleList.find(refEntityTag);
  if (tupleItr == tupleList.end())
    {
      // Found nothing    
        std::cout << "Tuple not found for ref-entity-tag " << refEntityTag << " " << std::endl;
        return false;
    }
    else
    {
       // Found nothing    
        *tuple = tupleItr->second;
        std::cout << "Tuple  found for ref-entity-tag " << refEntityTag << "(" << tuple  << ")" <<  std::endl;
        
        return true;
    }
}

int main()
{
  
    
  pcuTupleStrSearchT tupleList;
  int tupleValue = 0;

  tupleList["connection/20#element/15"]=10;
  tupleList["connection/20#element/15#bvc/127"]=30;
  tupleList["connection/20#element/15#cgi-cell/131858433"]=50;
  tupleList["connection/20#element/15#cell/131858433#tdma/3"]=70;
 


  if (true == findTuple(tupleList,"connection/20#element/15#bvc/127", &tupleValue))
  {
      
      std::cout << "returned tuple is " << tupleValue << std::endl;
  }
  
  

}
