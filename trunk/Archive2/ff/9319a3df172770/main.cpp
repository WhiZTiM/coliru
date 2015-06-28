#include<iostream>
using namespace std;
#include<list>
#include <algorithm>

template<class MESSAGE>
class BaseObserver{
public:
    virtual ~BaseObserver(){}
    virtual void notify(MESSAGE m) = 0;
};

class simpleEchoObserver : public BaseObserver < int > {
int * num;
public:
    simpleEchoObserver(int n = 0) :num(new int(n)){}
    ~simpleEchoObserver(){ delete num; num = 0; }
    void notify(int i){ *num += i; cout << *num << endl; }

};

template<class MESSAGE>
class Notifier{
    class Notify{
        MESSAGE message;
    public:
        Notify(MESSAGE m) :message(m){}
        void operator()(BaseObserver<MESSAGE>*o){ o->notify(message); }
};
    list <BaseObserver<MESSAGE>*> observers;
public:
    ~Notifier(){ for_each(observers.begin(), observers.end(), Notify(MESSAGE())); }
    void addObserver(BaseObserver<MESSAGE>*o){ observers.push_back(o); }
    void notify(MESSAGE m){ for_each(observers.begin(), observers.end(), Notify(m)); }
};

int main()
{
Notifier<int>notifier;
simpleEchoObserver s1(3), s2;
notifier.addObserver(&s1);
notifier.addObserver(&s2);
notifier.notify(7);
return 0;
}