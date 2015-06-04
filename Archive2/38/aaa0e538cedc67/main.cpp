#include <iostream>
#include <string>
#include <vector>

struct RapidDog {
    
};

template<class  T>  void  enemyAdjust(T  objparm)
{
  //objparm.moveposition();
  //objparm.fireweapon();
} 

template void enemyAdjust(RapidDog objparm);

int main()
{
    RapidDog obj;
    enemyAdjust(obj); // Incomplete type, error
    
    void(*fnPtr)(RapidDog); // Pointer to incomplete type, fine
}

