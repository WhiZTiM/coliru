#include <type_traits>

/** This is a base class that implements the watching behvaior */
class Watchable
{
    // Some stuff...
};

/** This is a pointer that let's you observe the lifetime of types extending "Watchable" */
template <typename T>
struct WatchPtr final
{
    // Some more stuff...
 
	// Make sure that "T" extends "Watchable"
	// static_assert(std::is_base_of<Watchable, T>::value, "...");
    // *** lazy static_assert: postpone evaluation till the constructor is instantiated  ***
    WatchPtr( T* p = nullptr ) : value(p)
	{ static_assert(std::is_base_of<Watchable, T>::value, "..."); }
 
private:
 
	T* value;
}; 

/** For various reasons, we have chosen to forward-declare this type */
class SomeTypeThatMustBeForwardDeclared;

/** This type wants to have a WatchPtr to "SomeType..." */
class SomeOtherType
{
	WatchPtr<SomeTypeThatMustBeForwardDeclared> value;
	// Here you get some crazy template errors
	// "But why? "SomeType..." is defined right below this!
	// You don't even really need the definition at this moment anyway!
	// Because fuck you, that's why.
};

/** Now we define it */
class SomeTypeThatMustBeForwardDeclared : public Watchable
{
	// Blah blah blah
};

int main() {
    SomeOtherType test ;  // constructor of WatchPtr<SomeTypeThatMustBeForwardDeclared>
                          // is now instantiated and the static_assert is evaluated
                          // at this pont, SomeTypeThatMustBeForwardDeclared is a complete type
}
