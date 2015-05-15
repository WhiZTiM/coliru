#include <tuple>
#include <iostream>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <vector>

using namespace std;

struct Foo1 {
    double bar= 0;
    double foo(int x) const { return 42.44; }
};

struct Foo2 {
    int bar = 0;
    auto foo(int x) { this->bar = x; return "ZZZ"; }
};

    
    template<typename T>
    T tt= 5.5;

auto foo1(int x) {
    //int a= 33;
    return [=](){ return x; };
}
auto ff(int x) {
    //int a= 33;
    return [=](){ return foo1(x)()*x; };
}

auto inc(bool setup=0) {
    int x=0;
    return [=]() mutable { return ++x; };
}

//int Foo1= 7;

auto f_a(int a, double b=1, string c="aa") {
    cout<<a<<' '<<b<<' '<<c<<endl;
}
auto f_bar(Foo2 f) {
    cout<< f.bar<<endl;
}

function<int (int)> f;

int main() {
    using namespace std;
    using namespace boost::fusion;
    
    f= [](int x){ return x*x; };
    
    auto fp= &f_a;
    
    fp(333, 1 ,"aa");
    
    //fp=11;
    
    typedef Foo2 FT;

    Foo2 foo2= {19};//= {foo1(11)};
    struct Foo1 foo1;
    
    foo2= FT{111};
    
    //cout<<foo2.bar<<endl;
    f_bar({333});
    
    
    tuple<Foo1&, Foo2&> t(foo1, foo2);

    for_each(t, [](auto& e) {
        auto x= e.foo(33);
        cout << x << endl;
        cout<<e.bar<<endl;
    });
    

    tt<double> = 5.5;
    cout << "foo2.bar after mutation: " << get<1>(t).bar<<' '<<foo2.bar << endl;
    foo2.foo(333);

    cout << "foo2.bar after mutation: " << foo2.bar << endl;
    
    //cout<< foo1(11) <<endl;
    
    vector<int> v{1,2,3};
    
    //if (v)
      //  cout<<1<<endl;
      
    auto f= ff(333);
    
    cout<< f() <<endl;
    
    auto f2= inc();
    
    cout<< f2() <<endl;
    cout<< f2() <<endl;
    cout<< f2() <<endl;
    
    tuple<int,int,string> T= {1,2};
    T= {1,2,"a"};
    
    for_each(T, [](auto& x) {
        cout<< x<<' ';
    });
    
    cout/*<< T */<<endl;
    f_a(1);//,2,"ert");
    //Foo1=11;
    f_a(1);//,2,"ert");
    
    string s="ert";
}