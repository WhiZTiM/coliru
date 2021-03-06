#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <string>

namespace cv
{
    template <typename T>
    struct Point_ { T x, y; };
    
    using Point2f = Point_<float>;
}

template <typename T>
struct point_type {};

template <typename T>
struct point_type<cv::Point_<T>> { using type = T; };

namespace boost {
  template <typename T, typename U = typename point_type<T>::type>
    T lexical_cast(const std::string &str)
    {
      std::vector<std::string> parts;
      boost::split(parts, str, boost::is_any_of(","));
      T R;
      R.x = boost::lexical_cast<U>(parts[0]);
      R.y = boost::lexical_cast<U>(parts[1]);
      return R;
    }
}

int main()
{
  auto p = boost::lexical_cast<cv::Point2f>(std::string("1,2"));
  std::cout << p.x << " " << p.y << std::endl;
  
  auto p2 = boost::lexical_cast<cv::Point_<double>>(std::string("3.0,4.0"));
  std::cout << p2.x << " " << p2.y << std::endl;
}
