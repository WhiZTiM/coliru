#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int leastElement(int arr[], int n, int start, int end) {
  if (start >= end -1) {
    return start;
  }
  else {
    int subLeastElement = leastElement (arr, n, start + 1, end);
    if (arr[start] <= arr[subLeastElement]) {
      return start;
    }
    else {
      return subLeastElement;
    }
  }
}

int leastElement(int arr[], int n) {
    return leastElement(arr, n, 0, n);
}

int main()
{
    int a[] = {2,5,1,4,3};
    std::cout << leastElement(a,5) << std::endl;
    
}
