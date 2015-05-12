#include <iostream>
#include <map>
#include <vector>

class Trackthis {
  public:
  Trackthis() {
  }
  Trackthis(const Trackthis&) {
      std::cout << "copy ctor";
  }
  Trackthis(Trackthis&&) {
      std::cout << "move ctor";
  }
};

struct ReturnObject {
    Trackthis o1;
    std::map<int, int> o2;
};

ReturnObject  function() {
    Trackthis o1;
    std::map<int, int> o2;
    
    return {o1, o2};
}

int main()
{
    ReturnObject destination = function();
}
