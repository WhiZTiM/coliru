#include <iostream>
#include <memory>

using std::shared_ptr;
#define FILL_CHAR '#'
#define COUNT 8

struct Animal
{
    virtual ~Animal(){}
    virtual void DoSomething(){std::cout << "Animal::DoSomething" << std::endl;}
    int a=0;
};

struct Dog : Animal
{
    void  DoSomething() override {std::cout << "Dog::DoSomething" << std::endl;}
    int b = 1;
};

void Add(shared_ptr<Animal> req)
{
    std::cout << "Add" << std::endl;
}

using animal_ptr =  shared_ptr<Animal>;
using dog_ptr = shared_ptr<Dog>;

int main()
{ 
    dog_ptr    dPtr1 (new Dog());
    animal_ptr dPtr2 (new Dog());  
    dPtr1->DoSomething();
    dPtr2->DoSomething();
    Add(dPtr1);
    Add(dPtr2);
    
  return 0;
}