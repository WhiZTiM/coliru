#include <iostream>
#include <memory>
 
template <typename T, typename Copy>
struct copyer : public T
{
    template <typename... Args>
	copyer(Args&&... args) : T(std::forward<Args>(args)...) {}
 
	copyer(const copyer& rhs) : T(Copy()(rhs)) {}
	copyer(copyer& rhs) : copyer(static_cast<const copyer&>(rhs)) {}
	copyer(copyer&&) = default;
	copyer& operator=(copyer&&) = default;
	copyer& operator=(const copyer& rhs) = default;
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
using copying_ptr = copyer<std::unique_ptr<T>, PtrCopy<T>>;
 
int main() 
{
	copying_ptr<int> p1 = new int(5);
	copying_ptr<int> p2 = p1;
	std::cout << p1.get() << " " << p2.get();
	return 0;
}