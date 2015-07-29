// Example program
#include <iostream>
#include <string>
#include <map>
struct comparator
{
    public:
    bool operator()(const std::string x, const std::string y)
    {
         return x.compare(y)<0;
    }
};

int main()
{
  std::map<std::string,int,comparator> map;
  std::string a="one";
  const char b[4]="one";
  std::string c("one",30);
  map[a]++;
  map[b]++;
  map[c]++;
  std::cout << map[a] << std::endl;
  std::cout << map.count(a) << std::endl;
}
