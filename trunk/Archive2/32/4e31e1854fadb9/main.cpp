#include <boost/optional.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>

void Test(const boost::filesystem::path& targetPath,
          const boost::optional<std::vector<std::wstring> >& filePath = boost::none)
{

}

int main() {
    std::vector<std::wstring> path(3, L"bla");

    Test("blabla", path);
    Test("blabla");
}
