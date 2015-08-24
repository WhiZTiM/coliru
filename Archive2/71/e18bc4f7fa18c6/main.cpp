#include <iostream>
#include <algorithm>
#include <random>

//return the index of the minimum element in array a
int min(const int * const a) {
  int m = a[0];
  int indx = 0;
  #define TEST(i) (m > a[i]) && (m = a[i], indx = i ); //see http://stackoverflow.com/questions/7074010/find-maximum-of-three-number-in-c-without-using-conditional-statement-and-ternar
  TEST(1);
  TEST(2);
  TEST(3);
  TEST(4);
  TEST(5);
  TEST(6);
  TEST(7);
  TEST(8);
  TEST(9);
  #undef TEST
  return indx;
}

void sort( int * const a ){
  static int work[10];
  int indx;
  #define GET(i) indx = min(a); work[i] = a[indx]; a[indx] = 2147483647; //get the minimum, copy it to work and set it at max_int in a
  GET(0);
  GET(1);
  GET(2);
  GET(3);
  GET(4);
  GET(5);
  GET(6);
  GET(7);
  GET(8);
  GET(9);
  #undef GET
  #define COPY(i) a[i] = work[i]; //copy back to a
  COPY(0);
  COPY(1);
  COPY(2);
  COPY(3);
  COPY(4);
  COPY(5);
  COPY(6);
  COPY(7);
  COPY(8);
  COPY(9);
  #undef COPY
}

int main() {
  //generating and printing a random array
  int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle( a, a+10, g);
  for (int i = 0; i < 10; i++) {
    std::cout << a[i] << ' ';
  }
  std::cout << std::endl;

  //sorting and printing again
  sort(a);
  for (int i = 0; i < 10; i++) {
    std::cout << a[i] << ' ';
  } 

  return 0;
}