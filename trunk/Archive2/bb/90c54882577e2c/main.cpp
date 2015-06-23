#include <iostream>
using namespace std;

template <class T>

class A
{
    class A_Impl
	{
		T var;
		int version;

	public:
		explicit A_Impl(T var1) : var(var1), version(1){};
		
		A_Impl(const A_Impl& a) : var(a.var), version(1){}

		const A_Impl& operator=(const A_Impl& a){
			var = a.var;
			++version;
			return *this;
		}

		operator T() const{
			return var;
		}

		friend class A < T > ;
	};

	A_Impl a;
public:
	A(T var) : a(var){}
	
	A_Impl& get(){ return a; }

	int version(){ return a.version; }
};

int main(){
    A<int> a1(5);
	cout << "a1 = " << a1.get() << endl << ", version = " << a1.version() << endl;

	//a1.get() = 7;
	cout << "a1 = " << a1.get() << endl << ", version = " << a1.version() << endl;

	A<int> a2 = a1;
	a1 = 13;
	cout << "a2 = " << a2.get() << endl << ", version = " << a2.version() << endl;
	cout << "a1 = " << a1.get() << endl << ", version = " << a1.version() << endl;
    
    return 1;
}