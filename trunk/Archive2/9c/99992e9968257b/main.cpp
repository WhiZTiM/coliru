#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>

using namespace std;

template<typename T>
class singleton{
    private:
        static T* m_instance;    
    public:
        singleton(){
            assert(m_instance==NULL);
            m_instance=static_cast<T*>(this);
            }
        virtual ~singleton(){m_instance=NULL;}
    static T& Getsingleton(){return *m_instance;}
    static T* GetsingletonPtr(){return m_instance;}  
    
    std::ostream& operator<<(const singleton<T>& vec)
    {
        std::ostream& os;
        for (auto& el : vec)
        {
           os << el << ' ';
        }
        return os;
    }
/*std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}*/
};

template<typename T>
T* singleton<T>::m_instance=nullptr;

class Manager:public singleton<Manager>
{
    private:
    
    public:
        void print()
        {
            cout<<"singleton manager succesfully printing!";
        }
        
};



template<typename T>
class Hacksingleton:public Manager
{
private:


public:


};

int main()
{
    new Manager;
    Manager& manager{Manager::Getsingleton()};
    manager.print();
    delete Manager::GetsingletonPtr();
    
}
