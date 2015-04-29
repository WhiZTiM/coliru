#include <iostream>
#include <list>

#define foreach(TYPE, ELEMENT, COLLECTION_TYPE, COLLECTION)\
for(COLLECTION_TYPE::iterator ELEMENT##MACRO_TEMP_IT = (COLLECTION).begin(); ELEMENT##MACRO_TEMP_IT != (COLLECTION).end(); ++ELEMENT##MACRO_TEMP_IT)\
for(bool ELEMENT##MACRO_B = true; ELEMENT##MACRO_B;)\
for(TYPE ELEMENT = *(ELEMENT##MACRO_TEMP_IT); ELEMENT##MACRO_B; ELEMENT##MACRO_B = false)

int main()
{
    std::list<int> indexes{1, 2, 3};
    
    foreach(int, i, std::list<int>, indexes)
    {
        std::cout << i << std::endl;
    }
    
    foreach(int, i, std::list<int>, indexes)
        std::cout << i << std::endl;
    
    std::list<std::list<int>> listOfLists{{1, 2}, {3, 4}};
    foreach(std::list<int>&, li, std::list<std::list<int>>, listOfLists)
        foreach(int, i, std::list<int>, li)
            std::cout << i << std::endl;
}
