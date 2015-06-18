#include <boost/optional.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

void Test(const boost::filesystem::path& targetPath, boost::optional<std::vector<std::wstring>& > filePath = boost::none) {
    if (filePath)
        std::cout << filePath->size() << " elements\n";
    else
        std::cout << "default parameter\n";
}

int main() {
    std::vector<std::wstring> path(3, L"bla");

    Test("blabla", path);
    Test("blabla");
}
