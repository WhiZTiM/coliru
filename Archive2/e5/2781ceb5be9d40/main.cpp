#include <iostream>
#include <vector>

using namespace std;

class GraphCode
{
public:
      friend ostream& operator <<(ostream& outStream, const GraphCode& graphCode);
      std::string toString() const
      {
          return "this is a graph";
      }
};

ostream& operator <<(ostream &outStream, const GraphCode& graphCode)
{
  outStream << graphCode.toString();
  return outStream;
}

int main()
{
    GraphCode g;
    std::cout << g << std::endl;
}