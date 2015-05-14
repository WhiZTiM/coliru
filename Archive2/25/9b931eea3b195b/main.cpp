#include <memory>
#include <iostream>
#include <functional>

using namespace std;

class Interface {
public:
  virtual void step() = 0;
  
  virtual ~Interface(){}
};

class Adapter : public Interface {
public:

  template< class T >
  void set_step(T t) {
      m_step = t;
  }

  void set_step_conversion(function<void(void)> t) {
      m_step=t;
  }

  void step() {
      if( m_step ) {
          m_step();
      }
  }
  
private:
  function<void(void)> m_step;
};

void foo(Interface& t) {
    t.step();
}

int print_two_numbers(double a, int b) {
  cout << a << " is a double" << endl;
  cout << b << " is an int" << endl;
  return b;
}

int main()
{   
    auto p = make_shared<Adapter>();
    p->set_step(
        [](){
            cout << "Hello world" << endl;
        }
        );
    foo(*p);
    auto x = 5.5f;
    auto y = 6;
    p->set_step_conversion(
        [x,y](){
            auto ret = print_two_numbers(x,y);
            cout << ret  << endl;
        }
        );    
    foo(*p);
    return 0;
}