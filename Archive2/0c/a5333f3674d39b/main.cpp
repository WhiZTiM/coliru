#include<iostream>
using namespace std;

//enum TStatus {  ok,sold,defect  };

class check {
private:
    enum TStatus {  ok,sold,defect  };

public:

    check();
    ~check();
    TStatus getStatus();

};




    check::check() { }

    check::TStatus check::getStatus()
    {
    //......
      return sold;
    }

    check::~check() { }


int main() {
    auto status = check().getStatus();

    std::cout << status << std::endl;
    }
    