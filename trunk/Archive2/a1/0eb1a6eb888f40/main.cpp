#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <pthread.h>

using namespace std;

class A {
  public:
  virtual ~A(){};
};

class B : public A {};

int main()
{
    A *a = new B;
    A *aa = new A;
    B *b = dynamic_cast<B *>(aa);
    if (b)
    cout << "success" << endl;
	return 0;
}