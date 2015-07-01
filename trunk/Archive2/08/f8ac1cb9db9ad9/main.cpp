#include <iostream>
#include <memory>
 
template <typename T, typename Copy>
struct value_ptr : public std::unique_ptr<T>
{
    template <typename... Args>
	value_ptr(Args&&... args) : std::unique_ptr<T>(std::forward<Args>(args)...) {}
    
	value_ptr(const value_ptr& rhs) : std::unique_ptr<T>(Copy()(rhs)) {}
	value_ptr(value_ptr& rhs) : value_ptr(static_cast<const value_ptr&>(rhs)) {}
	value_ptr(value_ptr&&) = default;
	value_ptr& operator=(value_ptr&&) = default;
	value_ptr& operator=(const value_ptr& rhs) = default;
};
 
template <typename T>
struct PtrCopy
{
	std::unique_ptr<T> operator()(const std::unique_ptr<T>& other)
	{
		return std::make_unique<T>(*other);
	}
};
 
template <typename T>
using copying_ptr = value_ptr<T, PtrCopy<T>>;
 
int main() 
{
	copying_ptr<int> p1 = new int(5);
	copying_ptr<int> p2 = p1;
	std::cout << p1.get() << " " << p2.get();
	return 0;
}