#include <cstdio>
#include <ctime>

struct tm tm_from_string(const char* str) {
    // look ma, no C++
    int year, month, day;
    struct tm tm = { 0 };
    if(sscanf(str, "%d-%2d-%2d", &year, &month, &day) != 3) {
        return tm;
    }
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    tm.tm_isdst = 0;
    if(std::mktime(&tm) == -1) {
        return tm; // TODO: error handling
    }
    return tm;
}

int main() {
    struct tm im_lazy = tm_from_string("2015-07-26");
    char buffer[100];
    if(!strftime(buffer, sizeof(buffer), "%Y-%m-%d", &im_lazy)) {
        printf("you're fucked friend\n");
    }
    printf("%s", buffer);
}