#include <iostream>
#include <string>
#include <vector>

typedef enum
{
    eAddMsgEvent = 1000
  //, eAnotherEvent = 10001 // main.cpp:23:12: warning: enumeration value 'eAnotherEvent' not handled in switch [-Wswitch]
} CustomEnum;

typedef enum
{
    eBla = 1
} SimulatedQEventType;


int main()
{

    int i;
    std::cin >> i;
    SimulatedQEventType x = eBla;
    switch (static_cast<CustomEnum>(x))
    {
        case eAddMsgEvent:
        break;
    }
}
