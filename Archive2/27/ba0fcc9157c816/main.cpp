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

template<typename TLeafType>
class level1
{

public:

    TLeafType* asLeaf(void)
        {return static_cast<TLeafType*>(this);}

    TLeafType const* asLeaf(void) const
        {return static_cast<TLeafType const*>(this);}

    template <Index N>
    auto getOutput(crPolyIndex c_Idx) const
        {return asLeaf() -> getOutputImpl(PortIdxType<N>{}, c_Idx);}

    static constexpr Natural getOutputPortsNumber(void)
        {return getOutputPortsNumberImpl<0>();}

    template<Index N, typename T = TLeafType>
    static constexpr std::enable_if_t<
        std::is_void<
            decltype(
                std::declval<T*>() ->
                template getOutput<N>(PolyIndex({}))
                )
        >::value,
            Index
            > getOutputPortsNumberImpl(void)
        {return N;}

    template<Index N, typename T = TLeafType>
    static constexpr std::enable_if_t<
        !std::is_void<
            decltype(
                std::declval<T*>() ->
                template getOutput<N>(PolyIndex({}))
                )
        >::value,
            Index
            > getOutputPortsNumberImpl(void)
        {return getOutputPortsNumberImpl<N + 1>();}

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

    // if void getOutputImpl(...) const is moved here from level1,
    // then the code compiles and works correctly.
    using level1<DataflowOutputClass<T>>::getOutputImpl;

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