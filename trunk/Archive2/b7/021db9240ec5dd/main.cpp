
#include <unordered_map>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


class mstring : public string {
public:
    using string::string;
    //mstring (char* p) : std::string(p) {};
    bool operator == (int x) {
        int n = atoi(this->c_str());
        return (n == x);
    }
};

int main(int /*argc*/, char *argv[])
{
    mstring t("123");
    if (t == atoi(argv[1])) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}