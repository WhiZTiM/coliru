/**
in this test , i will show you how to packed scoped_ptr and shared_ptr by template meta-function and 
how to create an instance (both struct and class) by scoped_ptr 

by Aimer

2015/5/11
*/

#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

template <typename T>
class scopedPtr 
{
public :
   typedef  boost::scoped_ptr<T> type ;
} ;


template <typename T>
class sharedPtr
{
public :
   typedef boost::shared_ptr<T> type ;
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
    std::cout << "======================================== scoped_ptr tests ================================================================" << std::endl ;
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
    
    std::cout << "======================================== shared_ptr tests ================================================================" << std::endl ;
    
    std::string name1 ("shared_ptr ---> kylin_zhang ") ;
    sharedPtr<FileManager>::type spFileManager( new FileManager(name1)) ;
    sharedPtr<node_t>::type spNode ( new node_t( name1 ) ) ;

    spFileManager->print() ;
    spNode->print () ;    
    
    // here we will test another way to create instances (class / struct ) by shared ptr
    
    sharedPtr<FileManager>::type spFileManager1  ;
    sharedPtr<node_t>::type spNode1 ;
    
    std::string name2("shared_ptr ----> naruto ") ;
    
    spFileManager1 = sharedPtr<FileManager>::type ( new FileManager ( name2)) ;
    spFileManager1->print () ;
    
    spNode1 = sharedPtr<node_t>::type ( new node_t ( name2) ) ;
    spNode1->print () ;
    
    /*
    here we got another conclusion :
    boost::shared_ptr support the second way to create an instance (struct/class)
    but the boost::scoped_ptr not 
    
    it must have soemthing to do with the authority transfer of scoped_ptr 
    */ 
    
    
    std::cout << "======================================== destructor call ================================================================" << std::endl ;
    std::cout << " next you will see , before the end of the program scoped_ptr will call the corresponding destruct methods" <<std::endl ; 
    
    
    return 0 ;
}
