using namespace std;

//enum TStatus {  ok,sold,defect  };

class check {
public:
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
      return TStatus::ok;
    }

    check::~check() { }


int main() {}
    