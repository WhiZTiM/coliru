#include <cstdio>

struct somestruct {
    int id;
    enum {
        STATE1 = 0,
        STATE2,
        STATE3,
        STATE4
    } state;
};

int main(int argc, char *argv[])
{
    static struct somestruct s;

    if (s.state == STATE1) {
        printf("state1\n");
    }

    return 0;
}