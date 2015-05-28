#include <iostream>
using namespace std;

#if __cplusplus > 199711
  #warning "New way here."
  //#error "Remove old code, uncomment new."
#else
  #warning "Old way here."
#endif

int main() {
    cout << __cplusplus << '\n';
	return 0;
}