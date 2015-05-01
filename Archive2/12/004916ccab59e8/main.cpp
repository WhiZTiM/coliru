#include <cstddef>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>
#include <iostream>

typedef size_t Index;
typedef unsigned long Natural;
typedef std::vector<Index> PolyIndex;
typedef const PolyIndex& crPolyIndex;
template<Index N> struct PortIdxType{};

template<typename X0, typename X1>
struct type_pair
{
    using T0 = X0;
    using T1 = X1;
};
template<typename T0, typename T1>
using first_type = typename type_pair<T0, T1>::T0;

template<typename TLeafType>
class level1
{

public:

    TLeafType* asLeaf(void)
        {return static_cast<TLeafType*>(this);}

    TLeafType const* asLeaf(void) const
        {return static_cast<TLeafType const*>(this);}

    template <Index N, typename T = TLeafType>
    auto getOutput(crPolyIndex c_Idx) const -> decltype(std::declval<T*>() -> getOutputImpl(PortIdxType<N>{}, c_Idx))
        {return asLeaf() -> getOutputImpl(PortIdxType<N>{}, c_Idx);}

    static constexpr Natural getOutputPortsNumber(void)
        {return getOutputPortsNumberImpl<0>(0);}

    template<Index N, typename T = TLeafType>
    static constexpr Index getOutputPortsNumberImpl(...)
        {return N;}

    template<Index N, typename T = TLeafType>
    static constexpr auto getOutputPortsNumberImpl(int)
        -> first_type<Index,
            decltype(
                std::declval<T*>() ->
                template getOutput<N>(PolyIndex({}))
                )
            >
    {return getOutputPortsNumberImpl<N + 1>(0);}

    template<Index N>
    void getOutputImpl(
        PortIdxType<N>, crPolyIndex c_Idx
        ) const
        {throw std::runtime_error("Wrong template argument.");}


};

template<typename T>
class DataflowOutputClass:
    public level1<DataflowOutputClass<T>>
{
public:
    //overload for when N = 0
    std::unique_ptr<double> getOutputImpl(
        PortIdxType<0>, crPolyIndex c_Idx
        ) const
    {
        std::unique_ptr<double> mydouble(new double(10));
        return mydouble;
    }

    //overload for when N = 1
    std::unique_ptr<int> getOutputImpl(
        PortIdxType<1>, crPolyIndex c_Idx
        ) const
    {
        std::unique_ptr<int> myint(new int(3));
        return myint;
    }

};


int main()
{
    DataflowOutputClass<int> a;
    std::cout << a.getOutputPortsNumber() << std::endl;
}