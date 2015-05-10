 #include <boost/fusion/include/vector.hpp>
 #include <boost/fusion/mpl.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/mpl/vector.hpp>
 
#include <boost/shared_ptr.hpp>

#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>

class obj1 
{
public :

    obj1( std::string name )
	{
		std::cout <<"create  "<<  name << std::endl ;
		_name = name ;
		
	}

	void print ()
	{
		std::cout<<"print  "  << _name  <<std::endl ;
	}
	
private :
	std::string _name ;
} ;

class obj2 
{
public :
	obj2( std::string n )
	{
		std::cout <<"create  "<<n << std::endl ;
		name = n ;
	}
	void print ()
	{
		std::cout <<"print  "<< name  <<std::endl ;
	}
	
private :
	std::string name ;
} ;

class obj3
{
public :
	obj3( std::string n )
	{
		std::cout <<"create  "<<n<< std::endl ;
		name = n ;
	}

	void print ()
	{
		std::cout<<"print  "  << name  <<std::endl ;
	}
	
private :
	std::string name ;
} ;

typedef boost::mpl::vector <obj1, obj2,obj3> CacheableTypes ;

template <typename T>
class sharedptr
{
public :
	typedef boost::shared_ptr<T> type ;
} ;

 	struct MakePair
	{
		template <typename T>
		struct apply
		{
			typedef boost::fusion::pair<T, typename sharedptr<T>::type > type ;
		} ;
	} ;

typedef boost::mpl::transform<CacheableTypes , MakePair>::type CachePair_t ;
typedef boost::fusion::result_of::as_map<CachePair_t>::type CacheMap_t ;




int main ()
{
	namespace fusion = boost::fusion ;
	namespace mpl = boost::mpl ;

	CacheMap_t mMap ;

	//obj1 o1("Aimer") ;
	//obj2 o2("Kokia") ;
	//obj3 o3("Rurutia") ;

	fusion::at_key<obj1>(mMap) = sharedptr<obj1>::type ( new obj1("obj1->Aimer")) ;
	sharedptr<obj1>::type p = fusion::at_key<obj1>(mMap) ;
	p->print() ;

	fusion::at_key<obj1>(mMap) = sharedptr<obj1>::type (new obj1("obj1->Kokia")) ;
	fusion::at_key<obj2>(mMap) = sharedptr<obj2>::type  (new obj2("obj2->rurutia")) ;
	fusion::at_key<obj3>(mMap) = sharedptr<obj3>::type (new obj3("obj3->inuyasha")) ;
	
	p = fusion::at_key<obj1>(mMap) ;
	p->print() ;

	return 0 ;
}