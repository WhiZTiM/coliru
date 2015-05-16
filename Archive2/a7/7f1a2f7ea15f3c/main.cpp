#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employee {
public:
    Employee(string thename, float thepayrate);
    string getName() const;
    float getPayRate() const;
    virtual float pay(float workhour);
protected:
    string name;
    float payrate;
};
class Manager : public Employee {
public:
    Manager(string thename, float thepayrate, bool isSalaried);
    float pay(float workhour);
protected:
    bool isSal;
};

Employee:: Employee(string thename, float thepayrate)
{
    name = thename;
    payrate = thepayrate;
}
string Employee::getName() const
{
    return name;
}
float Employee::getPayRate() const
{
    return payrate;
}
float Employee::pay(float workhour)
{
    cout << "Pay to " << name << " for " << workhour << " work hour" << endl;
    return payrate*workhour;
}

int main()
{   
    Employee emp("John Doe", 50.00);
    emp.pay(12.5);
}
