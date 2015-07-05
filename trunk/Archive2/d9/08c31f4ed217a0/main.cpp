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
  int *xs,*ys,*xe,*ye,i,j;
  int size_x    = 96;
  int size_y    = 96;
  int x_domains = 2;
  int y_domains = 4;
    int nproc=x_domains*y_domains;
  int xcell=(size_x/x_domains);
  int ycell=(size_y/y_domains);
  xs = (int *)malloc(nproc*sizeof(int));
  xe = (int *)malloc(nproc*sizeof(int));
  ys = (int *)malloc(nproc*sizeof(int));
  ye = (int *)malloc(nproc*sizeof(int));
  


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
  
  for(i=0;i<nproc;i++)
  { 
      std::cout << "rank " << i <<": xs:"<<xs[i]<<" xe:"<<xe[i]<<" ys:"<<ys[i]<<" ye:"<< ye[i]<< std::endl;
  }

}
