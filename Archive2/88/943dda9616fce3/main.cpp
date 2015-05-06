#include <string>

class Header
{
public:

};

class CanData : public Header
{
public:
  CanData() {
    str.resize(50);
  }
  std::string str;
};

int main() {
  Header *pt = new CanData();
  delete pt;
}