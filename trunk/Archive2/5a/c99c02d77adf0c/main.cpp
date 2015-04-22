#include <string>
#include <list>
#include <algorithm>

class A {
public:
  bool IsValid(std::string const& str) {
    std::list<Info>::iterator findIt;
    findIt = std::find(mInfo.begin(), mInfo.end(), str);
    return findIt != mInfo.end();
  }
private:
  struct Info {
    std::string someData;
    int         someData2;
    inline bool operator == (std::string const& rhs) {
      return someData == rhs;
    }
  };
  std::list<Info> mInfo;
};

int main(){}