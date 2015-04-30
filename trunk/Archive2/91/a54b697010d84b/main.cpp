#include <iostream>
#include <memory>
using namespace std;

void HexDump(void* data, uint32_t len) {
    unsigned char *buf = (unsigned char*)data;
    uint32_t i, j;
    char buffer[100 + 16 * (len / 16 + 1) + len * 5];
    char* output = buffer;

    output += sprintf(output, "\n");
    for (i = 0; i < len; i += 16) {
        output += sprintf(output, "%06x: ", i);
        for (j = 0; j < 16; j++) {
            if (i + j < len) {
                output += sprintf(output, "%02x ", buf[i + j]);
            } else {
                output += sprintf(output, "   ");
            }
        }
        output += sprintf(output, " ");
        for (j=0; j<16; j++) {
            if (i + j < len) {
                output += sprintf(output, "%c", isprint(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        output += sprintf(output, "\n");
    }
    cout << len << " bytes: " << endl;
    cout << buffer << endl;
}

struct Y {
    virtual void someCall1() = 0;
    virtual ~Y() {}
};
struct YY : public virtual Y {
    virtual ~YY() = default;
};
struct YYY : public virtual Y {
    virtual void someCall() = 0;
    virtual ~YYY() {}
};
struct X : public virtual Y, public virtual YYY/*, public virtual YY*/ {
    X() { a = 0.0; b = 0.0; c = false;}
    void someCall() override {}
    void someCall1() override {}
    double a;
    double b;
    bool c;
};

int main() {
    auto y = make_shared<X>();
    HexDump(y.get(), sizeof(X));
	return 0;
}