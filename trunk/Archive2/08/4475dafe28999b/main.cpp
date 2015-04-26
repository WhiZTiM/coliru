#include <iostream>
#include <boost/spirit/include/karma.hpp>
int main()
{
   int n,m;
   std::cin >> n >> m;

   std::cout.sync_with_stdio(false);
   int j=0;
   while (j <n) {
       int i = 0 ;
       while (i<m) {
               using boost::spirit::karma::int_;
               using boost::spirit::karma::generate;
               generate(std::ostreambuf_iterator<char>(std::cout), int_ << ',' << int_, i, j);
               i++;
        }
       j++;
   }
}
