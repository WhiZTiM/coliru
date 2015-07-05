#include <iostream>
#include <string>
#include <vector>
#include <math.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
//x : bit rate
//y : frame rate
// p: packet loss
int main()
{
  int *xs,*ys,*xe,*ye,*xs1,*ys1,*xe1,*ye1,i,j;
  int size_x    = 96;
  int size_y    = 96;
  int x_domains = 4;
  int y_domains = 4;
  int nproc=x_domains*y_domains;
  int xcell=(size_x/x_domains);
  int ycell=(size_y/y_domains);
  xs = (int *)malloc(nproc*sizeof(int));
  xe = (int *)malloc(nproc*sizeof(int));
  ys = (int *)malloc(nproc*sizeof(int));
  ye = (int *)malloc(nproc*sizeof(int));
  xs1 = (int *)malloc(nproc*sizeof(int));
  xe1 = (int *)malloc(nproc*sizeof(int));
  ys1 = (int *)malloc(nproc*sizeof(int));
  ye1 = (int *)malloc(nproc*sizeof(int));
  
  
  //original
  for(i = 0;i<nproc;i++){
    ys[i]=(y_domains-i%(y_domains)-1)*(ycell+2)+2;
    ye[i]=ys[i]+ycell-1;
  }

  for(i=0;i<=y_domains-1;i++) 
  {xs[i]=2;}

  for(i=0;i<=y_domains-1;i++) 
  {xe[i]=xs[i]+xcell-1;}

  for(i=1;i<=(x_domains-1);i++)
  { for(j=0;j<=(y_domains-1);j++) 
    {
      xs[i*y_domains+j]=xs[(i-1)*y_domains+j]+xcell+2;
      xe[i*y_domains+j]=xs[i*y_domains+j]+xcell-1;
    }
  }
  
  //from Yi Han
  for(i=0;i<nproc;i++)
  {
      ys1[i]=2+(y_domains-i%y_domains-1)*(ycell+2);
      ye1[i]=ys1[i]+ycell-1;
  }
  
  for(i=0;i<x_domains;i++)
  {
      for(j=0;j<y_domains;j++)
      {
          if(i==0)
          {
            xs1[j]=2;
            xe1[j]=xs1[j]+xcell-1;
          }else
          {
            xs1[i*y_domains+j]=xs1[(i-1)*y_domains+j]+xcell+2;
            xe1[i*y_domains+j]=xs1[i*y_domains+j]+xcell-1;
          }
      }
  }
  
  for(i=0;i<nproc;i++)
  { 
      std::cout << "rank " << i <<": xs:"<<xs[i]<<" xe:"<<xe[i]<<" ys:"<<ys[i]<<" ye:"<< ye[i]<< std::endl;
      std::cout << "rank " << i <<": xs1:"<<xs1[i]<<" xe:"<<xe1[i]<<" ys:"<<ys1[i]<<" ye:"<< ye1[i]<< std::endl;
  }
  
  

}
