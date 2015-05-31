#include <iostream>

class DamageType
{
  public:
     virtual void DamageFunction() { }
     virtual ~DamageType() {}
};

class DamageType1 : public DamageType
{
  public:
     void DamageFunction() { std::cout << "Do damage 1" << std::endl; }
};

class DamageType2 : public DamageType
{
  public:
     void DamageFunction() { std::cout << "Do damage 2" << std::endl; }
};

void displayDamage(DamageType* d)
{
   d->DamageFunction();
}

int main()
{
   DamageType1 d;
   DamageType2 d2;
   displayDamage(&d);
   displayDamage(&d2);
}