#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <memory>

class Tester
{
private:
    const std::string& m_name;

    Tester& operator=(const Tester&);

public:
    Tester(const std::string& name)
        : m_name(name)
    {
    }

    virtual ~Tester()
    {
    }

    const std::string& getName() const
    {
        return m_name;
    }
};

int main()
{
    const std::string s1("Filipe");
    std::shared_ptr<Tester> t1(new Tester(s1));
    
    const std::string s2("Florrie");
    std::shared_ptr<Tester> t2(new Tester(s2));

    std::cout << "String s1 (" << s1 << ") has been assigned to t1." << std::endl;
    std::cout << "String s2 (" << s2 << ") has been assigned to t2." << std::endl;

    std::cout << "Calling t1->getName() returns: " << t1->getName() << std::endl;
    std::cout << "Calling t2->getName() returns: " << t2->getName() << std::endl;

    std::swap(t1, t2);

    std::cout << std::endl;
    std::cout << "After calling std::swap(t1, t2), we expect the objects will have swapped places." << std::endl;
    std::cout << "Calling t1->getName() returns: " << t1->getName() << std::endl;
    std::cout << "Calling t2->getName() returns: " << t2->getName() << std::endl;
    
    return 0;
}
