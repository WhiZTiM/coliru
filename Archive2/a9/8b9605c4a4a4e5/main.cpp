#include <iostream>



class FlyType
{
    public:
       virtual void Move() = 0;
       virtual ~FlyType() { }
};


class CanFly : public FlyType
{
    public:
        void Move() override
        {
            std::cout << "Can fly\n";
        }
};


class CantFly : public FlyType
{
    public:
    void Move() override
        {
            std::cout << "Can't fly\n";
        }
};






class Bird 
{
    private:
             
    FlyType* m_flyType;
    std::string m_name;
      
      public:
         Bird(std::string name, FlyType* flyType)
         : m_flyType(flyType)
         , m_name(name)
         {
         }
         
         void Move()
         {
            std::cout << m_name << " ";
            m_flyType->Move();
         }
         
         

         
};


int main()
{
    Bird b ("Eagle", new CanFly());
    
    Bird o("Ostritch", new CantFly());
    
    b.Move();
    o.Move();
}