#include <iostream>
using namespace std;
void fstr(char *& strf){
    strf = "strf";
}
char * ptr = "";

int main(int argc, char** argv){
    fstr(ptr);
    cout << fstr;
    return 0;

}
