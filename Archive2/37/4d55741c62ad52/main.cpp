#include <string>
#include <iostream>
#include <vector>

bool isValidNum(const std::string & s) {
    int n = std::stoi(s);
    return (n >= 10 && n <= 26)? true:false;
}

int countNumRegular(const std::string & s) {
    if(s.length() == 0) return 1;
    if(s.length() == 1) return s[0] == '0'? 0:1;
    else {
        int n = 0;
        if(countNumRegular(s.substr(0,1)) == 1)
            n += countNumRegular(s.substr(1, s.length()-1));            
        if(isValidNum(s.substr(0,2)))
            n += countNumRegular(s.substr(2,s.length()-2));
        return n;
    }
}

int countNum(const std::string & s, std::vector<int> & b, int off) {
    if(s.length() == 0) return 1;
    if(s.length() == 1) return s[0] == '0'? 0:1;
    else {
        int n = 0;
        if(countNum(s.substr(0,1), b, 0) == 1) {
            int count = b[off+1];
            if(count == -1) {
                count = countNum(s.substr(1,s.length()-1), b, off+1);
                b[off+1] = count;
            }
            n += count;
        }
        if(isValidNum(s.substr(0,2))) {
            int count = b[off+2];
            if(count == -1) { 
                count = countNum(s.substr(2,s.length()-2), b, off+2);
                b[off+2] = count;
            }
            n += count;
        }
        return n;
    }
}

int countNum(const std::string & s) {
    std::vector<int> storage(s.length()+1, -1);
    return countNum(s, storage, 0);
}

int main() {
    std::string a;
    a = "41141"; std::cout << "a: " << a << " " << countNum(a) << " " <<   countNumRegular(a) << "\n";
    a = "11"; std::cout << "a: " << a << " " << countNum(a) << " " <<   countNumRegular(a) << "\n";
    a = "1"; std::cout << "a: " << a << " " << countNum(a) << " " <<   countNumRegular(a) << "\n";
    a = "1212"; std::cout << "a: " << a << " " << countNum(a) << " " <<   countNumRegular(a) << "\n";
    a = "5555"; std::cout << "a: " << a << " " << countNum(a) << " " <<   countNumRegular(a) << "\n";
    a = "111111111111111111111111111111"; std::cout << "a: " << a << " " << countNum(a) << " " << countNumRegular(a) << "\n";
    a = "3528719511183832221253"; std::cout << "a: " << a << " " << countNum(a) << " " <<  countNumRegular(a) << "\n";
}