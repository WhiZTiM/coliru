#include <iostream>
#include <cstring>
using namespace std;

void reverse(char *s)
{
    cout << s <<endl;
    int len = strlen(s);
    char *head = s;
    char *tail = &s[len-1];
    while (head < tail)
        swap(*head++, *tail--);
    cout << s <<endl;

}

int main(int argc, char* argv[]){
    for(int i = 1; i < argc; ++i){
        reverse(argv[i]);
    }
    return 0;
}
