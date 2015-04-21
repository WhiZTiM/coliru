#include <iostream>

using namespace std;

void f(float f, long int i) { cout << "1" << endl; }
void f(float f, float d) { cout << "2" << endl; }

int main() {

   f(5.0f, 5);
   
}