#include <iostream>
#include <vector>
#include <algorithm>

class spObj {
    int r;

  public:
    spObj() : r(0)                   { std::cout << "spObj constructed\n"; }
    spObj(const spObj &_r) : r(_r.r) { std::cout << "spObj copied\n"; }
   ~spObj()                          { std::cout << "spObj destroyed\n"; }
    spObj operator=(const spObj &_r) {
        this->r = _r.r;
        std::cout << "spObj assigned\n";
        return *this;
    }
};

template <typename Obj, typename Container = std::vector<Obj> >
class TSearchModule {
  private:
    Container container;

    TSearchModule(TSearchModule const&);
    TSearchModule& operator=(TSearchModule const&);
  public:
    TSearchModule() {}

    template <typename Cond>
    void Search(Cond const& cond) {
        while (cond(const_cast<TSearchModule const&>(*this))) {
            container.insert(container.end(), spObj());
        }
    }
    typename Container::iterator begin()       { return container.begin(); }
    typename Container::iterator end()         { return container.end(); }
             size_t              size()  const { return container.size(); }
};
//---------------------------------------------------------------------------

int main() {
    typedef TSearchModule<spObj> TSM;

    TSM myModule;
    myModule.Search([](TSM const& sm) { return sm.size() < 5; });

    int row_top;
    std::for_each(myModule.begin(), myModule.end(), [&row_top](spObj const&) { std::cout << "row_top: " << ++row_top << "\n"; });
}