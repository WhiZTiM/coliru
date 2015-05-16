#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employee {
public:
    Employee(string tName, float tRate) : name(tName), rate(tRate)  { }
    virtual ~Employee()  { }
    string getName() const {
        return name;
    }
    float getRate() const {
        return rate;
    }
    virtual float pay(float workhour) {
        cout << "Pay " << name << " for " << workhour << " work hour" << endl;
        return rate*workhour;
    }
protected:
    string name;
    float rate;
};

class Manager : public Employee {
public:
    Manager(string tName, float tRate, bool tIsSal) : Employee(tName, tRate), isSal(tIsSal)  { }
    
    bool getSalaried() const {
        return isSal;
    }
    virtual float pay(float workhour) {
        if (isSal) {
            cout << "Pay manager " << name << "(salaried) for " << workhour;
            cout << " work hour" << endl;
            return rate*workhour;
        }
        else{
            cout << "Manager " << name << " is not salaried." << endl;
            return 0;
        }
    }
protected:
    bool isSal;
};

int main() 
{
    Employee emp("John Doe", 50.00);
    Manager man("Mary Jane",  120.0, true);
    emp.pay(12.5);
    man.pay(20.0);
}
