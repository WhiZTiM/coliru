 #include<iostream>
    using namespace std;
    class C;
    class NoDefault{
    friend class C;
    public:
        NoDefault(int a) :item(a) {}   //lack default constructor
    private:
        int item;
    };
    class C{
    public:
        C() :item(1){}  //default constructor
        void print();
    private:
        NoDefault item;
    };
    void C::print()
    {
        cout<<item.item;
    }
    int main()
    {
        C obj1;
        obj1.print();
        return 0;
    }