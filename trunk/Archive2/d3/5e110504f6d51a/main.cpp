#include <iostream>
#include <vector>

float anglemod( float angle , float mod )
{
    return ( mod / 65536 ) * ( (int)( angle * ( 65536 / mod ) ) & 65535 );
}

int main()
{
    std::vector< float > nums = {
        -720.0 , -450.0 , -360.0 , -270.0 ,
        -180.0 , -90.0 , -45.0 ,  -0.0 ,
        0.0 , 45.0 , 90.0 , 180.0 ,
        270.0 , 360.0 , 450.0 , 720.0 ,
    };
    
    for( auto& num : nums )
    {
        std::cout << "anglemod360( " << num << " ) = "
        << anglemod( num , 360.0 ) << std::endl;
    }
    
    for( auto& num : nums )
        std::cout << "anglemod180( " << num << " ) = "
        << anglemod( num , 180.0 ) << std::endl;
    
    return 0;    
}
