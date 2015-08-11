#include <iostream>
using namespace std;

constexpr size_t power_of_two(size_t power)
{
   return !power ? size_t{ 1 } : 2 * power_of_two(power - 1); // could be optimized
}

constexpr size_t smallest_power_of_two_exceeding(size_t sz, size_t power = 0)
{
   return power_of_two(power) > sz
      ? power_of_two(power)
      : smallest_power_of_two_exceeding(sz, power + 1);
}

constexpr size_t smallest_fitting_alignment(size_t sz)
{
   return !sz ? size_t{} // this was the behaviour in your function, but throwing might be nicer
              : smallest_power_of_two_exceeding(sz) / 2;
}

int main()
{
   for (int i = 0; i < 20; ++i)
      cout << "Smallest fitting alignment for object of size "
           << i << ": " << smallest_fitting_alignment(i) << endl;
}