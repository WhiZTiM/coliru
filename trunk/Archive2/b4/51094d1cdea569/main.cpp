// find the next larger integer from the given number's digits
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: nexti <integer>\n";
        return -1;
    }
    char *str = argv[1];
    int const last = strlen(str) - 1;
    if (last <= 0)
        std::cout << str << '\n';
    auto i = last;
    // find the number smaller than the previous from last, the pivot
    // e.g. for 132959642 we'd stop at 9 i.e. just before 5, the pivot
    while ((i > 0) && (str[i-1] >= str[i]))
        --i;
    if (i == 0) {
        std::cout << "No larger may be formed with given digits.\n";
        return 0;
    }
    // substring to be actually fixed; everything before pivot is in tact
    // in our example, str would be pointing to 5 now
    str = &str[i - 1];
    // this substring is verified to be in descending order, except the most significant digit
    // reverse it excluding the MSD
    for (auto c = 0; c < ((last - i + 1) / 2); ++c)
        std::swap(argv[1][i + c], argv[1][last - c]);
    // find the next number larger than the pivot
    // in our example, we'd now have 132952469, find 6 and swap it with 5
    i = 1;
    while (str[i] <= *str) ++i;
    // swap that with the pivot
    std::swap(*str, str[i]);
    std::cout << argv[1];
}
