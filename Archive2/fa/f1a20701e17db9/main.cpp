template <bool bBOOL>
struct SFoo {};

struct STrait
    {
        template <bool bBOOL>
        using TFoo = SFoo<bBOOL>;
   };

template <typename tTRAIT>
struct SBar
    {
        template <bool B>
        using MyTFoo = typename tTRAIT::template TFoo<B>;
        
        template <bool> friend class MyTFoo;
    };

SBar<STrait> bar;

int main(){}