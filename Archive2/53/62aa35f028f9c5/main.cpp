#include <iostream>
#include <thread>
using namespace std;

template<class F> // Meta-programming
class Launch {
   thread th;
   public:
   Launch(F f) : th(move(f)) { }
   ~Launch() { th.join(); }  // RAII!
   // Automatically waits for thread termination before deleting this.
};

template<class F>
auto DoLaunch(F f) -> Launch<F> {  // I hide template complexity!
   return {f};
}

class Func {
   float val;
   public:
   Func(float val) : val(val) { }
   void operator()() {  // I'm a function AND an object.
      cout << "Sleeping.\n";
      this_thread::sleep_for(chrono::seconds(1));
      cout << val << endl;
   }
};

int main() {
   Func f(5);  // Storing 5.
   cout << "Calling manually.\n";
   f();
   cout << "Done calling manually.\n";
   cout << "Launching thread as temporary.\n";
   DoLaunch(f);
   cout << "Done with temporary.\n";
   cout << "Launching thread kept in scope.\n";
   auto&& th = DoLaunch(f);
   cout << "Done with main.\n";
   return 0;
}
