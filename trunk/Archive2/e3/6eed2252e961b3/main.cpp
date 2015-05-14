#include <iostream>
#include <stack>

void push_data( std::stack<std::pair<int,int>> & data, int & new_data )
{
    if ( data.size() > 0 )
        data.push( std::make_pair(new_data, std::min(new_data, data.top().second)) );
    else
        data.push( std::make_pair(new_data, new_data) );
}

int main()
{
    std::stack<std::pair<int,int>> data;
    
    int values[] = {10,9,8,7,6,5,4}; // 4 is the oldest obtained value, 10 is the newest
    
    for ( auto && v : values )
        push_data( data, v );
        
    while( !data.empty() )
    {
        std::cout << "current min = " << data.top().second << std::endl;
        data.pop();
    }
        
}