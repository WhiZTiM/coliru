#include <iostream>
#include <type_traits>

template < typename T > struct stype { using type = typename T::svar_type ; };

template < typename T > struct A
{
    static const typename std::decay<T>::type svar1 ;

    using svar_type = const typename std::decay<T>::type ;
    static svar_type svar2 ;

    using svar_type_alias = typename stype< A<T> >::type ;
    static svar_type_alias svar3 ;

    static svar_type svar4 ;
    static svar_type svar5 ;

};

// fine: const typename std::decay<T>::type is a type-dependent name, and it refers to the current instantiation
template < typename T > const typename std::decay<T>::type A<T>::svar1 {} ; // value-initialised

// fine: typename A<T>::svar_type is a type-dependent name, and it refers to the current instantiation
template < typename T > typename A<T>::svar_type A<T>::svar2 {} ; // value-initialised

// fine: typename stype< A<T> >::type is a type-dependent name, and it refers to the current instantiation
template < typename T > typename stype< A<T> >::type  A<T>::svar3 {} ; // value-initialised

// *** error: though typename stype< A<T> >::type is a type-dependent name, it does not refer to the current instantiation
template < typename T > typename stype< A<T> >::type  A<T>::svar4 {} ; // value-initialised

// *** error: decltype( A<T>::svar5 ) is a value-dependent name, not a type-dependent name
template < typename T > typename std::remove_reference< decltype( A<T>::svar5 ) >::type A<T>::svar5 {} ;

int main()
{
}
