#include <iostream>
#include <string>
#include <boost/regex.hpp>

bool bmatch(const std::string& x, const std::string& re_) {
  const boost::regex re(re_, boost::regex::icase);
  boost::smatch what;
  return boost::regex_match(x, what, re);
}

int main()
{
  std::string re = "^xy(?(?!z).*ending$|.*$)";
  std::vector<std::string> vx = { "XYZ124f5sf", "xyz12345",
                                  "XY38fsj dfENDING", "xy4 dfhd ending",
                                  "XYZ", "XY345kENDI", "xy56NDING" };
  for (auto i : vx) {
    std::cout << "\nString '" << i;
    if (bmatch(i, re)) {
      std::cout <<
        "' was matched." << std::endl;
     } else {
      std::cout <<
        "' was not matched." << std::endl;
     }
  }

  return 0;
}