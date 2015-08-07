#include <string>

template<typename T>
void error_with_type(T);

int main() {
    std::string text("asdffffffffff.f");
    for (const auto &s : text){
        error_with_type(s); 
    }
}