#include <cstring>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

class A {
    public:
    int n = 0;
    A(const char* p) { n = strlen(p); };

    A(A const&) = delete;
    void operator=(A const&) = delete;
    ~A() { printf("~A at %p\n", (void*)this); }
};
void F(vector<pair<const char*, const A&>> v) {
    printf("F\n");
    for(vector<pair<const char*, const A&>>::iterator it = v.begin();it!=v.end();++it) printf("  '%s': %p %i\n", it->first, &it->second, it->second.n);
};

int main(int, char**) {
    F({
            { "A", "A" },
            { "B", "BB" },
            { "C", "CCC" },
            { "D", "DDDD" }
        });
};