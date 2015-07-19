#include <map>
#include <memory>
#include <string>

int main() {
    std::map<std::string, std::unique_ptr<int>> mymap;
}