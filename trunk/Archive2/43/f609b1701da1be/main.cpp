#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std ;
using namespace boost ;
class Manager
{
public :
    Manager ( )
	{}

	void registerCallBack ( boost::function<void ()> f )
	{
		cout << " in manager call input function " << endl ;
		fds.push_back(f) ;
	}

	void runCallBack ()
	{
		cout<< "running method defined in Node" << endl ;

		for ( int i = 0;i < fds.size() ; i++ )
		{
			boost::function<void()> f = fds[i] ;
			f() ;
		}

		fds.clear() ;
	}


private :
	std::vector<boost::function<void()> > fds ;

} ;

class Node : public boost::enable_shared_from_this<Node>
{
public :
	Node () {}
	Node ( Manager *managerPtr )
	{
		pManager = managerPtr ;
	}
	void Aimer (   )
	{
		cout << " Aimer : hello i am Aimer "   << endl ; 
	}

	void Kokia (  )
	{
		cout << " Kokia : hello i am Kokia "   << endl ;
	}

	void Kylin (   )
	{
		cout << " Kylin Zhang : ..... - _ - ......" << endl ;
	}

	void start ()
	{
		cout << " in method start " << endl ;
		pManager->registerCallBack(boost::bind(&Node::Aimer ,  shared_from_this() )) ;
	 	pManager->registerCallBack(boost::bind(&Node::Kokia ,  shared_from_this())) ;
	 	pManager->registerCallBack(boost::bind (&Node::Kylin , shared_from_this ())) ;
	}

	Manager *pManager ;
} ;

class Obj : public boost::enable_shared_from_this<Obj> 
{
public :
	Obj ( Manager *pManager )
	{
		managerPtr = pManager ;
	}

	void start()
	{
		managerPtr->registerCallBack( boost::bind (&Obj::func1 , shared_from_this ()) ) ;
		managerPtr->registerCallBack( boost::bind ( &Obj::func2 , shared_from_this () )) ;
	}

	void func1()
	{
		cout << "func1 running "<< endl ;
	}

	void func2 ()
	{
		cout << "func 2 running " << endl ;
	}

private :
	Manager* managerPtr ;
} ;


int main ()
{
	Manager* pManager = new Manager() ;

	

	boost::shared_ptr<Node> nodePtr ( new Node ( pManager) ) ;
	
	
	boost::shared_ptr<Obj> objPtr ( new Obj (pManager) ) ;


	cout << " now i would like register methods defined in class Node into Manager function<void()> list " << endl ;
	nodePtr->start() ;
	cout << " now register methods in class Obj into Manager , by input parameter the pointer of class Manager instance " << endl ;
	objPtr->start () ;

	cout <<" ------------------------ run  method----------------------------" << endl ;
	pManager->runCallBack() ;

 
	return 0 ;
}
 
 