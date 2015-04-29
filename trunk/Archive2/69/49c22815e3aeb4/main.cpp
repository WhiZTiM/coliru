#include <iostream>
#include <string>
#include <vector>

typedef enum
{
    eAddMsgEvent = 1000
  , eAnotherEvent = 10001 // main.cpp:23:12: warning: enumeration value 'eAnotherEvent' not handled in switch [-Wswitch]
} CustomEnum;

typedef enum
{
    eBla = 1
} SimulatedQEventType;

bool do_something_important(SimulatedQEventType x)
{
    switch (static_cast<CustomEnum>(x))
    {
        case eAddMsgEvent:
        // add message...
        return true;
    }
    return false;
  
}


int main()
{
    {
      auto x = static_cast<SimulatedQEventType>(eAddMsgEvent);
      std::cout << "handled and valid enum:" << do_something_important(x) << std::endl;
    }
    
    {
      SimulatedQEventType x = eBla;   
      std::cout << "unhandled but valid enum:" << do_something_important(x) << std::endl;
    }
    
    {
      int i = 4242;
      SimulatedQEventType x = (SimulatedQEventType)i;  // das sollte man nie, nie, nie machen, aber Entwickler sind auch nur Menschen
      // c style casts should never be done in C++...
      std::cout << "invalid enum:" << do_something_important(x) << std::endl;
    }
    
}
