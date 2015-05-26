#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  cout << argc << endl;
  if (argc>0) {
    main(argc-1, argv+1);
    cout << "My arguments in reverse are:  " << argv[0] << endl;
  }
}
