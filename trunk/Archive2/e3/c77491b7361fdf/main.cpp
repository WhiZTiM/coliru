#include<string>

using namespace std;

typedef struct STR_1 {    
  int val_a, val_b;

  STR_1 (int a, int b)
  { val_a = a; val_b = b; }    
} STR_1;

typedef struct STR_2{    
      string name;
      STR_1 myStr1;

      STR_2 (string n, STR_1 s) : name(n), myStr1(s) {}
    } STR_2;

int main()
{
    return 0;
}