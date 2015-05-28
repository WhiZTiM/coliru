#include <string>

struct data {
    std::string country;
    std::string fathername;
    int   age;
};

int main() {
    data name[5] = {
        {"Saudi Arabia","Tahir Awan",24},
        {"England","Akram Khan",20},
        {"China","Amjad Ali",20},
        {"Syria","Ahmad Ali",19},
        {"Oman","Zohaib Sultan",24}
    };
}