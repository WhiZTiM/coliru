#include<map>
#include<tuple>


class Y
{
public:
    const int getId()  { return 1;}
    const int getSubId(){ return 2;}
   
};

struct comparator
  {
      bool operator ()(  Y &y1,  Y &y2) {
         return std::pair<int,int>( y1.getId(), y1. getSubId()) ==
          std::pair<int,int>( y2.getId(), y2. getSubId());
      }
   };

int main()
{
  
std::map<Y, Y, comparator> detailsMap;
}