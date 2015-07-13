#include <iostream>
#include <string>
#include <vector>

enum class STATUS
{
    STATUS_OFF = 0,
    STATUS_ON = 1
};

STATUS commonFunction()
{
    return STATUS::STATUS_ON;
}

class class1
{
    STATUS lightState;

public:
    void setLight(){lightState = commonFunction();}
};


int main()
{
  
}
