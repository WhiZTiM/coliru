#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;

namespace fs = boost::filesystem;

int main() {
    fs::path p1 = "/";
    fs::path p2 = p1 / fs::path("filename") / ".ext";
    
    std::cout << p1 << " " << p2 << std::endl;
	return 0;
}