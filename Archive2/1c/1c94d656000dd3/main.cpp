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

int main()
{   
    auto p = make_shared<Adapter>();
    p->set_step(
        [](){
            cout << "Hello world" << endl;
        }
        );
    foo(*p);
    return 0;
}