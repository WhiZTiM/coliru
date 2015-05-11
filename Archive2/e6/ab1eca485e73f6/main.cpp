#include <cstdio>
#include <iostream>

#include <boost/shared_ptr.hpp>

template <typename T>
class sharedPtr
{
    public :
     typedef boost::shared_ptr<T> type ;
} ;

typedef struct node
{
    std::string name ;
    node () : name(NULL)
    {}
    node ( std::string &n ) : name (n )
    {}
    
    ~node ()
    {
        std::cout << "release node " << name << std::endl ;
    }
        
    void print ()
    {
        std::cout << "node name " << name << std::endl;
    }
    
} node_t ;


template <typename T>
class shared_node
{
public :
    shared_node ( typename sharedPtr<T>::type& n )  :node ( n )
    {
         // n->print () ;
        
    }
  /*  
    this constructor will not change the counter , because , it re-new an object 
    instead of create a pointer lets multi-pointers point to a same object's space
    
    shared_node ( typename sharedPtr<T>::type n ) : node ( new T( *n) )
    {
      //  node = typename sharedPtr<T>::type ( new T(*n) ) ; // counter == 1
    }
*/
    void print ()
    {
        std::cout<< "reference counter : " << node.use_count() << std::endl ;
        node->print () ;
    }
private :
    typename sharedPtr<T>::type node ;
} ;


template <typename T>
void print_func ( typename sharedPtr<T>::type n)
{
    std::cout << "reference counter :" << n.use_count() << std::endl ;
    n->print () ;
}

int main ()
{
    std::string name ("kylin_zhang") ;
    
    std::cout << "================= print_func shows=======================" <<std::endl ;
    
    sharedPtr<node_t>::type  p ( new node_t (name) ) ;  // use counter = 1 
    
    print_func<node_t>(p) ;   // use counter = 2 , after get out of method , counter = 1
    
    std::cout << "================= shared_node print shows=======================" <<std::endl ;
    
 //   sharedPtr<shared_node<node_t> >::type s1(p) , s2(p) ;
    
   shared_node<node_t> s1(p) , s2(p) ;

   std::cout << "p 's use counter " << p.use_count () << std::endl;  // p's counter = 3
   
   s1.print () ;  // counter =1 
  
   s2.print () ;  // s2's p's counter =1 
   
   
   while ( p.use_count() != 0 )
    {
        std::cout << "use counter " << p.use_count() << std::endl ;
        p.reset() ; 
        
        // theory until p's use_counter == 0 , will p call delete method to release the space , if use_counter != 0 only executing use_counter-- operation
        // but , in practice , p.reset() once , p.use_count() == 0 , what this hell ? i do not clear 
    }    
    std::cout << "================= destructor shows=======================" <<std::endl ;
    return 0 ;
}

