#include <iostream>
#include <string>

int textToTagImpl(const char* arr);

struct ConstCharStar{
    ConstCharStar(const char* arr) : arr(arr) {}
    const char* arr;
};

int textToTag(const ConstCharStar& s);

template <unsigned int N>
int textToTag(const char (&arr)[N]){
    return textToTagImpl(arr);
}

// cpp file

static constexpr char vec[][5] = {"c", "miao", "biao", "liao", "gatt"};

template <unsigned int i>
int index(const char (&arr)[5]){
    return ((arr[0] << 24) ^ (arr[1] << 16) ^ (arr[2] << 8) ^ (arr[3])) == ((vec[i][0] << 24) ^ (vec[i][1] << 16) ^ (vec[i][2] << 8) ^ (vec[i][3])) ? i : index<i-1>(arr);
}

template <>
int index<0>(const char (&arr)[5]){
    const unsigned int i = 0;
    return ((arr[0] << 24) ^ (arr[1] << 16) ^ (arr[2] << 8) ^ (arr[3])) == ((vec[i][0] << 24) ^ (vec[i][1] << 16) ^ (vec[i][2] << 8) ^ (vec[i][3])) ? i : -1;
}

int textToTag(const ConstCharStar& s){
    return textToTagImpl(s.arr);
}

template <>
int textToTag<1>(const char(&arr)[1]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({'\0', '\0', '\0', '\0', '\0'});
}

template <>
int textToTag<2>(const char(&arr)[2]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({arr[0], '\0', '\0', '\0', '\0'});
}

template <>
int textToTag<3>(const char(&arr)[3]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({arr[0], arr[1], '\0', '\0', '\0'});
}

template <>
int textToTag<4>(const char(&arr)[4]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>({arr[0], arr[1], arr[2], '\0', '\0'});
}

template <>
int textToTag<5>(const char(&arr)[5]){
    return index<sizeof(vec)/sizeof(vec[0]) - 1>(arr);
}

int textToTagImpl(const char* arr){
    std::cout << "last resort" << std::endl;
    for(auto i = 0u; i < 5u; ++i){
        if(std::string{arr} == vec[i]){
            return i;
        }
    }
    return -1;
}

int main()
{
    std::cout << textToTag("c") << std::endl;
    std::cout << textToTag("miao") << std::endl;
    std::cout << textToTag("biao") << std::endl;
    std::cout << textToTag("liao") << std::endl;
    std::string gatt{"gatt"};
    std::cout << textToTag(gatt.c_str()) << std::endl;
    
    std::cout << textToTag("gatto") << std::endl;
    std::string gatto{"gatto"};
    std::cout << textToTag(gatto.c_str()) << std::endl;
    
    
    std::cout << textToTag("quick brown fox") << std::endl;
}
