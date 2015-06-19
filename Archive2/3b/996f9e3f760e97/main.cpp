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
      return check::ok;
    }

    check::~check() { }


int main() {}
    