#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <functional>

class A
{
  private: //Dummy Values
    int x;
    int y;
  public:
    bool operator==(A const& other) const
    {
      return x == other.x && y == other.y;
    }
};

class B
{
  private:
    std::vector <A> dataHandler;

  public:
    bool isElement(A element);
    //Should return true if element exists in dataHandler
};

bool B::isElement(A element)
{
  return std::find(dataHandler.begin(), dataHandler.end(), element) != dataHandler.end();
}

int main()
{}
