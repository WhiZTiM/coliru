/**
in this test , i will show you how to packed scoped_ptr by template meta-function and 
how to create an instance (both struct and class) by scoped_ptr 

by Aimer
*/

#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>

#include <boost/scoped_ptr.hpp>

template <typename T>
class scopedPtr 
{
public :
   typedef  boost::scoped_ptr<T> type ;
} ;

typedef struct node 
{
    node () : file_name(NULL) , fp(NULL)
    {}
    node ( std::string &path ) : file_name ( path ) 
    {
        fp = fopen (path.c_str() , "r") ;
        
       // assert ( fp ) ;
    }
    
    ~node ()
    {
        std::cout << "release node_t " << file_name << std::endl ;
    }
    
    void print ()
       {
           std::cout << "node open " << file_name << std::endl ;
       }

    std::string file_name ;
    FILE* fp ;
    
}node_t ;

class FileManager
{
    public :
       FileManager () : file_name ( NULL ) , fp( NULL )
       {}
       FileManager ( std::string &name )
       {
          file_name = name ;
          
          fp = fopen ( file_name.c_str() , "r" ) ;
          
          //assert (fp) ;
       }
       
       ~FileManager ()
       {
         std::cout << "release FileManager " << file_name << std::endl ;
       }
       
       void print ()
       {
           std::cout << "FileManager open " << file_name << std::endl ;
       }
    private :
     std::string file_name ;
     FILE *fp ;
} ;


int main ()
{
    std::string name = "aimer.txt" ;
   /*
    FileManager *pFileManger = new FileManager( name ) ;
    node_t* pNode = new node_t (name ) ;
    */

// here is how to create an instance (class/struct type) by boost::scoped_ptr by its constructor 

    scopedPtr<FileManager>::type pFileManager ( new FileManager( name ) ) ;
    scopedPtr<node_t>::type pNode ( new node_t(name) ) ;
    
    scopedPtr<FileManager>::type pFileManager1 ;
    scopedPtr<node_t>::type pNode1 ;
    
// here is another way to create an instance (class/struct type) by boost::scoped_ptr by its constructor
// it works well on shared_ptr but doesn't work well on scoped_ptr
//    std::string name_ = "kokia.txt" ;
    
//    pFileManager1 =  scopedPtr<FileManager> ( new FileManager (name_)  )  ; 
//    pNode1        = scopedPtr<node_t>::type ( new node_t (name_)) ;


// here is how to use boost::scoped_ptr to call the instance's function 
    
    pFileManager->print () ; 
    
    pNode->print () ;
    
  
    
    std::cout << " next you will see , before the end of the program scoped_ptr will call the corresponding destruct methods" <<std::endl ; 
    
    
    return 0 ;
}
