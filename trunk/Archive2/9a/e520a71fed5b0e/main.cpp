#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


template<typename T1, typename T2>
void TSave(const std::string fname, const T1& p1, const T2& p2) {
    std::string filename = fname;
    std::stringstream data;

    data << p1 << "\n";
    data << p2 << "\n";

    std::ofstream outfile(filename);
    outfile.write(data.str().c_str(), data.str().size());
    outfile.close();
}

class A
{
public:
  A() : name(""), age(0) {};

  void Save(void)
  {
    TSave("A.txt", name, age);
  }

  std::string name;
  int age;
};

class B
{
public:
  B() : ID(0), points(0) {};

  void Save(void)
  {
    TSave("B.txt", ID, points);
  }

  int ID;
  int points;
};

int main(void)
{
  A a;
  B b;

  a.name = "Bob"; a.age    = 20;
  b.ID   = 4;     b.points = 95;

  a.Save();
  b.Save();

  return 0;
}