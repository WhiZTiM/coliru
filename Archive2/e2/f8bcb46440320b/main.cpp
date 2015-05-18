#include <iostream>


class CanFly
{
    public:
        void Move()
        {
            std::cout << "Can fly\n";
        }
};


class CantFly
{
    public:
    void Move()
        {
            std::cout << "Can't fly\n";
        }
};


template<typename T>
class Bird : public T
{
    private:
      std::string m_name;
      
      public:
         Bird(std::string name) 
         : m_name(name)
         {
         }
         
         void Move()
         {
            std::cout << m_name << " ";
            T::Move();
         }
};


int main()
{
    Bird<CanFly> b ("Eagle");
    
    Bird<CantFly> o("Ostritch");
    
    b.Move();
    o.Move();
}