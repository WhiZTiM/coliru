#include <iostream>
#include <cstdio>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace std ;

 class  obj : public boost::enable_shared_from_this<obj>  
{
    public :
        void runCallBack ( boost::function<int(int,int)> f   , int x , int y ) 
        {
    		cout <<   f( x, y ) << endl ;
        }

        int  myadd (  int x , int y )
        {
             return x+y ;
        }
    
        void setCallBack ( int x , int y  )
        {
			   
			runCallBack(   boost::bind( &obj::myadd , shared_from_this () , _1 , _2  ) ,x , y  )    ;
        }
        
        private :
            boost::function<int( int ,int )> f;
			 
} ;

int main ()
{
    
    boost::shared_ptr<obj> pObj ( new obj ()) ;
    
    pObj->setCallBack(999, 1) ;
    
 
    return 0 ;
}