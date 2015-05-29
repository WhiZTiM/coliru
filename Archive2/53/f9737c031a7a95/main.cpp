#include <vector>
#include <algorithm>
#include <iostream>

class ExpensiveClass {
public:
  static int increment;
  std::vector<int> bigVector;

  ExpensiveClass() {
    for (int j = 0; j < 1 + increment; ++j)
      bigVector.emplace_back(j);
    ++increment;
  }
  ExpensiveClass(const ExpensiveClass& other) {
    std::cout << "Expensive copy constructor called!" << std::endl;
    this->bigVector = other.bigVector;
  }
};

int ExpensiveClass::increment = 0;

bool sortFunc(const ExpensiveClass& a, const ExpensiveClass& b) {
  bool ret = a.bigVector < b.bigVector;
  if (ret == false)
    std::cout << "Need to swap" << std::endl;
  return ret;
}

int main()
{
  std::vector<ExpensiveClass> vectorOfVectors;
  vectorOfVectors.reserve(100);
  for (int i = 0; i < 100; ++i)
    vectorOfVectors.emplace_back();

  std::cout << "Start sorting.." << std::endl;
  std::sort(vectorOfVectors.begin(), vectorOfVectors.end(), sortFunc);
}