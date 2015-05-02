#include <iostream>
#include <string>
#include <vector>

int leastElement(int arr[], int start, int end) {
  if (start >= end -1) {
    return start;
  }
  else {
    int subLeastElement = leastElement (arr, start + 1, end);
    if (arr[start] <= arr[subLeastElement]) {
      return start;
    }
    else {
      return subLeastElement;
    }
  }
}

int leastElement(int arr[], int n) {
    return leastElement(arr, 0, n);
}

int main()
{
    int a[] = {2,5,1,4,3};
    std::cout << leastElement(a,5) << std::endl;
    
}
