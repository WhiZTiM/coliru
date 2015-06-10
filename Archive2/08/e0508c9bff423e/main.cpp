// high_resolution_clock example
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <limits>

int main ()
{
  using namespace std::chrono;

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  std::cout << "if (i & 0x80000000) == 0)... ";
  int sum = 0;
  //for (int k = 0; k < std::numeric_limits<int>::max(); k++) {
  //for (int j = 0; j < std::numeric_limits<int>::max(); j++) {
    for (int i = 0; i < std::numeric_limits<int>::max() / 32; i++) {
        if ((i & 0x80000000) == 0) sum++;
    }
  //}
  //}
  std::cout << "SUM: " << std::hex << std::showbase << sum << std::dec << " (" << sum << ")" << std::endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "TIME: " << time_span.count() * 1000.0 << " ms";
  std::cout << std::endl;

  return 0;
}