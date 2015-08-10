#include <boost/log/core/record_view.hpp>

struct A
{
   boost::log::record_view view;
};

int main()
{
   const A a = {};
   A b;
   b = a;

   const boost::log::record_view r;
   boost::log::record_view rr;
   rr = r;
}