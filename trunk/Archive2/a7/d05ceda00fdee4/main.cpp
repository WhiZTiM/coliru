#include <iostream>
#include <limits.h>

enum class AddressType_t : uint8_t
{
    STANDARD_ADDRESS = 0,
    ENHANCED_ADDRESS = 1,
};

class Address 
{
    public:
       virtual AddressType_t GetAddressType() 
       { 
           throw std::invalid_argument( "Address Type not implemented!" ); 
       };
};

class StdCommandAddress : public Address 
{
    public:
       AddressType_t GetAddressType() 
       { 
           return AddressType_t::STANDARD_ADDRESS;
       };
};

class EnhCommandAddress : public Address 
{
    public:
       AddressType_t GetAddressType() 
       { 
           return AddressType_t::ENHANCED_ADDRESS;
       };
};

class EktCommandAddress : public Address 
{
};

void RunCommand( Address *address )
{
    std::cout << "Address Type:" << ((int)address->GetAddressType()) << std::endl;
}

int main()
{
    RunCommand( new StdCommandAddress() );
    RunCommand( new EnhCommandAddress() );
    RunCommand( new EktCommandAddress() );
    
}
