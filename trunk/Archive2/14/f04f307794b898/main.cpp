#include <tuple>
#include <utility>
#include <typeinfo>


struct Omit{} omit;


template <class Field, class ...Fields>
struct TupleHolder{
    using fieldT = Field;
    using nextT = TupleHolder<Fields...>;

    Field field;
    TupleHolder<Fields...> next;

    TupleHolder(){}

    template <class ...ValuesRef>
    TupleHolder(Omit, ValuesRef&& ... values)
            : next( std::forward<ValuesRef>(values)... )
    {}

    template <std::size_t ...ids, class FieldValue, class ...ValuesRef>
    TupleHolder(std::index_sequence<ids...>, FieldValue&& field, ValuesRef&& ... values)
    :
            field( std::get<ids>(std::forward<FieldValue>(field))... ),
            next( std::forward<ValuesRef>(values)... )

    {}


    template <class FieldValue, class ...ValuesRef>
    TupleHolder(FieldValue&& field, ValuesRef&& ... values)
            : TupleHolder(
                  std::make_index_sequence<
                          std::tuple_size< std::decay_t<FieldValue> >::value
                  >(),
                  std::forward<FieldValue>(field),
                  std::forward<ValuesRef>(values)...
            )
    {}

};


template <class Field>
struct TupleHolder<Field>{
    using fieldT = Field;
    Field field;    // actually last

    TupleHolder(){}
    TupleHolder(Omit){}

    template <std::size_t ...ids, class FieldValue>
    TupleHolder(std::index_sequence<ids...>, FieldValue&& field)
            :
            field( std::get<ids>(std::forward<FieldValue>(field))... )
    {}


    template <class FieldValue>
    TupleHolder(FieldValue&& field)
            : TupleHolder(
            std::make_index_sequence<
                    std::tuple_size< std::decay_t<FieldValue> >::value
            >(),
            std::forward<FieldValue>(field)
    )
    {}
};



template <int index, int target_index, class T>
struct GetLoop{
    using type = typename T::nextT;

    constexpr static decltype(auto) get(T& data) noexcept{
        return GetLoop<index+1, target_index, typename T::nextT>::get(
                data.next
        );
    }

    constexpr static decltype(auto) get(const T& data) noexcept{
        return GetLoop<index+1, target_index, typename T::nextT>::get(
                data.next
        );
    }


    constexpr static decltype(auto) get(T&& data) noexcept{
        return GetLoop<index+1, target_index, typename T::nextT>::get(
                std::forward<type>(data.next)
        );
    }
};

template <int target_index, class T>
struct GetLoop<target_index, target_index, T>{
    using type = typename T::fieldT;

    constexpr static type& get(T& data) noexcept{
        return data.field;
    }

    constexpr static const type& get(const T& data) noexcept{
        return data.field;
    }

    constexpr static type&& get(T&& data) noexcept{
        return std::forward<type>(data.field);
    }
};


// ----------------------------------------------------------------------------------
//                          F R O N T E N D
// ----------------------------------------------------------------------------------

template<class ...FieldTypes>
struct TuplePiecewise{
    using fieldsT = TupleHolder<FieldTypes...>;
    TupleHolder<FieldTypes...> data;

    TuplePiecewise(){}

    template <class ...ValuesRef>
    explicit constexpr TuplePiecewise(ValuesRef&& ... values) noexcept
            : data( std::forward<ValuesRef>(values)... ){}

    TuplePiecewise( const TuplePiecewise& other ) = default;
    TuplePiecewise( TuplePiecewise&& other ) = default;


    static constexpr const std::size_t size = sizeof...(FieldTypes);
};


// ----------------------------------------------------------------------------------
// Return &/const&/&& correctly (almost exact copy from )
// ----------------------------------------------------------------------------------


template<int index, class ...FieldTypes>
constexpr decltype(auto) get(TuplePiecewise<FieldTypes...> &&list) noexcept {
    return GetLoop<0, index, typename TuplePiecewise<FieldTypes...>::fieldsT >::get(  std::move(list.data) );
}

template<int index, class ...FieldTypes>
constexpr decltype(auto) get(TuplePiecewise<FieldTypes...> &list) noexcept {
    return GetLoop<0, index, typename TuplePiecewise<FieldTypes...>::fieldsT >::get(  list.data );
}

template<int index, class ...FieldTypes>
constexpr decltype(auto) get(const TuplePiecewise<FieldTypes...> &list) noexcept {
    return GetLoop<0, index, typename TuplePiecewise<FieldTypes...>::fieldsT >::get(  list.data );
}




// -----------------------------------------------------------------
//              TEST



#include <iostream>

using namespace std;


struct CopyTest {
    int i = 100;
    int j = -100;
    CopyTest(int i, int j) : i(i), j(j) {
        cout << "default ctr" << endl;
    }

    CopyTest(const CopyTest &other) {
        cout << "Copy ctr" << endl;
    }

    CopyTest(CopyTest &&other) noexcept /* noexcept needed to enable optimizations in containers */
    {
        cout << "Move ctr" << endl;
    }

    ~CopyTest() noexcept /* explicitly specified destructors should be annotated noexcept as best-practice */
    {
        cout << "Destructor" << endl;
    }

    CopyTest &operator=(const CopyTest &other) {
        cout << " Copy assignment operator" << endl;
        return *this;
    }

    /** Move assignment operator */
    CopyTest &operator=(CopyTest &&other) noexcept {
        cout << " Move assignment operator" << endl;
        return *this;
    }
};


// rvalue ref test
template <class T>
void fn_test_my(T&& value){
    decltype(auto) oref = get<0>(forward<T>(value));
    cout << is_rvalue_reference<decltype(value)>::value <<endl;
    cout << is_rvalue_reference<decltype(oref)>::value <<endl;
}


int main()
{
    int i = 400;

    TuplePiecewise< CopyTest&&, int&, string, int >
    list (forward_as_tuple(CopyTest(45,63)), forward_as_tuple(i), forward_as_tuple("hghhh"), omit );

    decltype(auto) o = get<0>(list);
    cout << o.i << endl;
    
    cout << "-----------------------------------" << endl;
    fn_test_my(TuplePiecewise< tuple<CopyTest&&> >(forward_as_tuple(CopyTest(45,63))));

    cout << "-----------------------------------" << endl;
    // nested
    TuplePiecewise< string, TuplePiecewise<int,int> > list4
    (forward_as_tuple("RRR"), forward_as_tuple(forward_as_tuple(10), forward_as_tuple(20)));

   cout << get<0>(get<1>(list4));
   return 0;
}