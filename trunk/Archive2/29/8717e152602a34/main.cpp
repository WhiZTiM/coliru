#include <functional>
#include <iostream>
#include <vector>

template<typename BidiIter, typename CBidiIter,
         typename Compare = std::less<typename BidiIter::value_type>>
int next_comb(BidiIter first, BidiIter last,
              CBidiIter /* first_value */, CBidiIter last_value,
              Compare comp=Compare()) {
  /* 1. Find the rightmost value which could be advanced, if any */
  auto p = last;
  while (p != first && !comp(*(p - 1), *--last_value)) --p;
  if (p == first) return false;
  /* 2. Find the smallest value which is greater than the selected value */
  for (--p; comp(*p, *(last_value - 1)); --last_value) { }
  /* 3. Overwrite the suffix of the subset with the lexicographically smallest
   *    sequence starting with the new value */
  while (p != last) *p++ = *last_value++;
  return true;
}

int main(int argc, char** argv) {
  std::vector<int> values = {1,2,2,3,3,3,3};
  /* Since that's sorted, the first subset is just the first k values */

  const int k = 2;
  std::vector<int> subset{values.cbegin(), values.cbegin() + k};

  /* Print each combination */
  do {
    for (auto const& v : subset) std::cout << v << ' ';
    std::cout << '\n';
  } while (next_comb(subset.begin(), subset.end(),
                     values.cbegin(), values.cend()));
  return 0;
}
                     
                     