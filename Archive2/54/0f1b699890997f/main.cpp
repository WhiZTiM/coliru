#define BOOST_PYTHON_MAX_ARITY 16
#include <boost/python.hpp>

// Functions have 5 parameters per line.

/// @brief Mockup spam function with 14 parameters.
double spam(
  int, int, int, int, int, // 5
  int, int, int, int, int, // 10
  int, int, int, int       // 14
)
{
  return 42;
}

/// @brief Mockup spam function with 16 parameters.
boost::python::list spam(
  int, int, int, int, int, // 5
  int, int, int, int, int, // 10
  int, int, int, int, int, // 15
  int                      // 16
)
{
  boost::python::list list;
  return list;
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;

  double (*spam_14)(
    int, int, int, int, int, // 5
    int, int, int, int, int, // 10
    int, int, int, int       // 14
  ) = &spam;

  python::list (*spam_16)(
    int, int, int, int, int, // 5
    int, int, int, int, int, // 10
    int, int, int, int, int, // 15
    int                      // 16
  ) = &spam;

  python::def("spam", spam_14);
  python::def("spam", spam_16);
}