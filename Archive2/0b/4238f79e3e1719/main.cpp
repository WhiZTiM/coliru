#include <iostream>
#include <type_traits>
#include <utility>
#include <memory>

#include <tuple>
#include <memory>
#include <type_traits>

namespace my
{

namespace detail
{

namespace unwrap_traits
{
    template<
        typename /*DecayedFunction*/,
        bool /*IsMember*/,
        bool /*IsConst*/,
        bool /*IsVolatile*/>
    struct unwrap_trait_base;

    /// Unwrap base
    template<
        typename ReturnType, typename... Args,
        bool IsMember,
        bool IsConst,
        bool IsVolatile>
    struct unwrap_trait_base<ReturnType(Args...), IsMember, IsConst, IsVolatile>
    {
        ///  The decayed type of the function without qualifiers.
        using decayed_type = ReturnType(Args...);

        /// The return type of the function.
        using return_type = ReturnType;

        /// The argument types of the function as pack in std::tuple.
        using argument_type = std::tuple<Args...>;

        /// Is true if the given function is a member function.
        static constexpr bool is_member = IsMember;

        /// Is true if the given function is const.
        static constexpr bool is_const = IsConst;

        /// Is true if the given function is volatile.
        static constexpr bool is_volatile = IsVolatile;
    };

    template<typename ClassType>
    struct class_trait_base
    {
        /// Class type of the given function.
        using class_type = ClassType;
    };

    /// Function unwrap trait
    template<typename /*Fn*/>
    struct unwrap_trait;

    /// Function
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(Args...)>
        : unwrap_trait_base<ReturnType(Args...), false, false, false> { };

    /// Const function
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(Args...) const>
        : unwrap_trait_base<ReturnType(Args...), false, true, false> { };

    /// Volatile function
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(Args...) volatile>
        : unwrap_trait_base<ReturnType(Args...), false, false, true> { };

    /// Const volatile function
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(Args...) const volatile>
        : unwrap_trait_base<ReturnType(Args...), false, true, true> { };

    /// Function pointer
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(*)(Args...)>
        : unwrap_trait_base<ReturnType(Args...), false, false, false> { };

    /// Const function pointer
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(*const)(Args...)>
        : unwrap_trait_base<ReturnType(Args...), false, true, false> { };

    /// Volatile function pointer
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(*volatile)(Args...)>
        : unwrap_trait_base<ReturnType(Args...), false, false, true> { };

    /// Const volatile function pointer
    template<typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(*const volatile)(Args...) >
        : unwrap_trait_base<ReturnType(Args...), false, true, true> { };

    /// Class method pointer
    template<typename ClassType, typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(ClassType::*)(Args...)>
        : unwrap_trait_base<ReturnType(Args...), true, false, false>,
          class_trait_base<ClassType> { };

    /// Const class method pointer
    template<typename ClassType, typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(ClassType::*)(Args...) const>
        : unwrap_trait_base<ReturnType(Args...), true, true, false>,
          class_trait_base<ClassType> { };

    /// Volatile class method pointer
    template<typename ClassType, typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(ClassType::*)(Args...) volatile>
        : unwrap_trait_base<ReturnType(Args...), true, false, true>,
        class_trait_base<ClassType> { };

    /// Const volatile class method pointer
    template<typename ClassType, typename ReturnType, typename... Args>
    struct unwrap_trait<ReturnType(ClassType::*)(Args...) const volatile>
        : unwrap_trait_base<ReturnType(Args...), true, true, true>,
        class_trait_base<ClassType> { };

} // namespace unwrap_traits

template<typename /*Fn*/>
struct move_only_wrapper_impl;

template<typename ReturnType, typename... Args>
struct move_only_wrapper_impl<ReturnType(Args...)>
{
    virtual ~move_only_wrapper_impl() { }

    virtual ReturnType operator() (Args&&...) = 0;

}; // struct move_only_wrapper_impl

template<typename /*Fn*/>
struct wrapper_impl;

template<typename ReturnType, typename... Args>
struct wrapper_impl<ReturnType(Args...)>
    : move_only_wrapper_impl<ReturnType(Args...)>
{
    virtual ~wrapper_impl() { }

    // virtual wrapper_impl* clone() = 0;

}; // struct wrapper_impl

template<typename /*Fn*/>
struct fake_wrapper_impl;

template<typename ReturnType, typename... Args>
struct fake_wrapper_impl<ReturnType(Args...)>
    : wrapper_impl<ReturnType(Args...)>
{
    ReturnType operator() (Args&&...) override
    {
        return ReturnType();
    }

}; // struct fake_wrapper_impl

template<typename /*Fn*/, bool /*NonCopyable*/, bool /*Constant*/, bool /*Volatile*/>
class function;

template <typename CRTP>
struct call_operator;

template <typename ReturnType, typename... Args, bool NonCopyable>
struct call_operator<function<ReturnType(Args...), NonCopyable, true, false>>
{
    using func = function<ReturnType(Args...), NonCopyable, true, false>;
    
    ReturnType operator()(Args&&... args) const
    {
        return (*static_cast<const func*>(this)->_impl)(std::forward<Args>(args)...);
    }
};

template <typename ReturnType, typename... Args, bool NonCopyable>
struct call_operator<function<ReturnType(Args...), NonCopyable, true, true>>
{
    using func = function<ReturnType(Args...), NonCopyable, true, true>;
    
    ReturnType operator()(Args&&... args) const volatile
    {
        return (*static_cast<const volatile func*>(this)->_impl)(std::forward<Args>(args)...);
    }
};

template<typename ReturnType, typename... Args, bool NonCopyable, bool Constant, bool Volatile>
class function<ReturnType(Args...), NonCopyable, Constant, Volatile> : public call_operator<function<ReturnType(Args...), NonCopyable, Constant, Volatile>>
{
    friend struct call_operator<function<ReturnType(Args...), NonCopyable, Constant, Volatile>>;
    
    std::unique_ptr<wrapper_impl<ReturnType(Args...)>> _impl;

public:
    function()
        : _impl(new fake_wrapper_impl<ReturnType(Args...)>()) { }
        
    using call_operator<function<ReturnType(Args...), NonCopyable, Constant, Volatile>>::operator();    
}; // class function

} // namespace detail

template<typename Signature>
using function = detail::function<
    typename detail::unwrap_traits::unwrap_trait<Signature>::decayed_type,
    true /*NonCopyable*/,
    detail::unwrap_traits::unwrap_trait<Signature>::is_const /*Constant*/,
    detail::unwrap_traits::unwrap_trait<Signature>::is_volatile /*Volatile*/
>;

/// Creates a function object from the given parameter
template<typename Fn>
auto make_function(Fn&& functional)
{
    // TODO
    return std::forward<Fn>(functional);
}

} // namespace my


// Tests:

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    TD<decltype(&my::function<void (int) const>::operator())>();
    
    TD<decltype(&my::function<void (int) const volatile>::operator())>();
}
