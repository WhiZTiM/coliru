#include <iostream>
#include <list>
#include <algorithm>

void output_lists(const std::list<std::list<std::string>>& collection)
{
    for( auto& list_in_collection : collection )
    {
        for( auto& entry : list_in_collection )
        {
            std::cout << entry << ',';
        }
        std::cout << std::endl;
    }
}

int main() {
    std::list<std::list<std::string>> collection;
    collection.push_back( std::list<std::string>{"5","6","7","8","9"} );
    collection.push_back( std::list<std::string>{"3","2","1"} );
    collection.push_back( std::list<std::string>{"10","20","30","40","50"} );
    
    // print out the inputs for inspection
    
    output_lists(collection);
    
    // demonstrate using std::for_each()
    
    std::list<std::list<std::string>> collection_for_for_each = collection;
    
    std::for_each(
        collection_for_for_each.begin(),
        collection_for_for_each.end(),
        [](std::list<std::string>& list_in_collection )
        {
            if(list_in_collection.size() < 4)
            {
               list_in_collection.push_back( "NULL" );   
            }
        }
    );
    
    output_lists(collection_for_for_each);
    
    // demonstrate using std::transform
    
    std::list<std::list<std::string>> collection_for_transform = collection;

    std::transform(
        collection_for_transform.begin(),
	    collection_for_transform.end(),
	    collection_for_transform.begin(),
        [](std::list<std::string>& list_in_collection )
        {
            if(list_in_collection.size() < 4)
            {
               list_in_collection.push_back( "NULL" );   
            }
            return list_in_collection;
        }
    );
    
    output_lists(collection_for_transform);
    
    
   return 0;
}
