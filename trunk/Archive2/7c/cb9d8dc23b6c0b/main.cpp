#include <string>

template<typename>
void error_with_type();

int main() {
    std::string text("asdffffffffff.f");
    for (const auto &s : text){
        error_with_type<decltype(s)>(); 
    }
}