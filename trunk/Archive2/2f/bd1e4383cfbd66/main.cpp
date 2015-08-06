

#include<iostream>
//#include<conio.h>

using namespace std;
 class rectangle
 {
  double length,width;
  public:
         rectangle()
         {
          length=0;
          width=0;
          }
         rectangle(double len,double wid)
          {
           length=len;
           width=wid;
           }
           double display()
           {
            return(length*width);
            }
           rectangle operator+(rectangle& rect)
            {
             rectangle recta;
             recta.length=this->length+rect.length;
             recta.width=this->width+rect.width;
             return rectangle(length,width);
             }
             };
             int main()
             {
            // rectangle rect1,rect2,rect3;
              rectangle rect1(7.0,8.9);
              rectangle rect2(11.4,12.8);
              rectangle rect3=rect1+rect2;
             cout<<rect1.display()<<endl;
             cout<<rect2.display()<<endl;
             cout<<rect3.display()<<endl;
             //getch();
             return 0;
             }


