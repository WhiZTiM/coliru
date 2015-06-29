#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  int book_code = 0;

  cout << "Please enter the four digit book code: ";
  cin >> book_code;
  string code = to_string(book_code);
  cout << code << endl;

} 