#include <iostream>
#include <string>
#include <vector>

std::string genSomething(std::string arg = "!") { return "wow" + arg; }

struct DaMan
{
    int age = 12;
    float wat = 10.42;
    std::string wouh = " it works!";
    std::string wow = genSomething();
    std::string yeah = genSomething(" YEAH");
    std::string uh = genSomething(wouh); // because wouh is initialized first (member name apparition order is initialization order)
    std::string nope = genSomething(eh); // for the same reason, this cannot work right as eh is define after
    std::string eh = "????";
};

int main()
{
    DaMan man;
    std::cout << man.wow << std::endl;
    std::cout << man.yeah << std::endl;
    std::cout << man.uh << std::endl;
    std::cout << man.nope << std::endl;
    
}
