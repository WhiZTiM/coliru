#include <iostream>
#include <list>

#define foreach(TYPE, ELEMENT, COLLECTION_TYPE, COLLECTION)\
for(COLLECTION_TYPE::iterator ELEMENT##_MACRO_TEMP_IT = COLLECTION.begin(); ELEMENT##_MACRO_TEMP_IT != COLLECTION.end(); ++ELEMENT##_MACRO_TEMP_IT) \
for(bool ELEMENT##_MACRO_B = true; ELEMENT##_MACRO_B;)\
for(TYPE ELEMENT = *(ELEMENT##_MACRO_TEMP_IT); ELEMENT##_MACRO_B; ELEMENT##_MACRO_B = false)

int main()
{
    std::list<int> indexes{1, 2, 3};
    
    foreach(int, i, std::list<int>, indexes)
    {
        std::cout << i << std::endl;
    }
    
    foreach(int, i, std::list<int>, indexes)
        std::cout << i << std::endl;
}
