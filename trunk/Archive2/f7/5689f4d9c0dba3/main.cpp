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
  int *xs,*ys,*xe,*ye,*ze,*zs,i,j,l,m,k,v,p;
  int size_x    = 32;
  int size_y    = 32;
  int size_z    =32;
  int x_domains = 2;
  int y_domains = 2;
  int z_domains =2;
    int nproc=x_domains*y_domains*z_domains;
  int xcell=(size_x/x_domains);
  int ycell=(size_y/y_domains);
  int zcell=(size_z/z_domains);
  xs = (int *)malloc(nproc*sizeof(int));
  xe = (int *)malloc(nproc*sizeof(int));
  ys = (int *)malloc(nproc*sizeof(int));
  ye = (int *)malloc(nproc*sizeof(int));
   zs =(int *) malloc(nproc*sizeof(int));
  ze =(int *) malloc(nproc*sizeof(int)); 


   for(i=1;i<=y_domains;i++) {
    ys[(i-1)*z_domains]=y_domains*(ycell+2)-ycell*i-2*(i-1);
    ye[(i-1)*z_domains]=ys[(i-1)*z_domains]+ycell-1;

    for(l=1;l<=z_domains-1;l++) {
      ys[(i-1)*z_domains+l]=ys[(i-1)*z_domains];
      ye[(i-1)*z_domains+l]=ys[(i-1)*z_domains+l]+ycell-1;
    }
  }

  /* prolongation along x_domain */

  for(m=1;m<=y_domains;m++) {
    ys[(m-1)*z_domains]=y_domains*(ycell+2)-ycell*m-2*(m-1);
    ye[(m-1)*z_domains]=ys[(m-1)*z_domains]+ycell-1;

    for(i=1;i<=x_domains-1;i++) {
      ys[i*(y_domains*z_domains)+(m-1)*z_domains]=ys[(m-1)*z_domains];
      ye[i*(y_domains*z_domains)+(m-1)*z_domains]=ys[i*(y_domains*z_domains)+(m-1)*z_domains]+ycell-1;

      for(l=1;l<=z_domains-1;l++) {
        ys[i*(y_domains*z_domains)+(m-1)*z_domains+l]=ys[i*(y_domains*z_domains)+(m-1)*z_domains];
        ye[i*(y_domains*z_domains)+(m-1)*z_domains+l]=ys[i*(y_domains*z_domains)+(m-1)*z_domains+l]+ycell-1;
      }
    }
  }

  /* computation of xs and xe with topoly process */

  for(i=0;i<=(z_domains*y_domains)-1;i++) {
    xs[i]=2;
    xe[i]=xs[i]+xcell-1;
  }

  for(j=1;j<=x_domains-1;j++) {
    for(k=0;k<=(z_domains*y_domains-1);k++) {    
      xs[j*(z_domains*y_domains)+k]=xs[(j-1)*(z_domains*y_domains)]+xcell+2;
      xe[j*(z_domains*y_domains)+k]=xs[j*(z_domains*y_domains)]+xcell-1;
    }
  }

  /* computation of zs and ze with topoly process */

  for(k=0;k<=y_domains-1;k++) {
    v=k*z_domains;
    zs[v]=2;
    ze[v]=2+zcell-1;

    for(p=1;p<=x_domains-1;p++) {
      zs[v+p*(y_domains*z_domains)]=zs[v];
      ze[v+p*(y_domains*z_domains)]=ze[v];
    }
  }

  /* prolongation along z_domain */

  for(m=1;m<=z_domains-1;m++) {
    for(i=0;i<=y_domains-1;i++) {
      l=m+i*z_domains;
      zs[l]=zs[l-1]+zcell+2;
      ze[l]=zs[l]+zcell-1;

      for(v=1;v<=x_domains-1;v++) {
        zs[l+v*(y_domains*z_domains)]=zs[l];
        ze[l+v*(y_domains*z_domains)]=zs[l+v*(y_domains*z_domains)]+zcell-1;
      }
    }
  }
  
  for(i=0;i<nproc;i++)
  { 
      std::cout << "rank " << i <<": xs:"<<xs[i]<<" xe:"<<xe[i]<<" ys:"<<ys[i]<<" ye:"<< ye[i]<< " zs:"<<zs[i]<<" ze:"<< ze[i]<<std::endl;
  }

}
