#include <boost/variant/variant.hpp>

template <typename T>
struct Deferred
{
    typedef T value_type;
};

template <typename T>
struct DeferredContainer
{
	typedef typename T::value_type value_type;
};

class DictionaryObject;
class MixedArrayObject;

using DictionaryObjectPtr = DeferredContainer < DictionaryObject >; // DeferredContainer<DictionaryObject>
using MixedArrayObjectPtr = Deferred < MixedArrayObject >; // DeferredContainer<MixedArrayObject>

typedef boost::variant <
	MixedArrayObjectPtr,
	DictionaryObjectPtr
> ContainerPtr;

class MixedArrayObject
{
public:
	typedef int value_type;

	inline void SetContainer(ContainerPtr obj) { _container = obj; }
	inline ContainerPtr GetContainer() const { return _container; }

private:
	ContainerPtr _container;
};

class DictionaryObject
{
public:
	typedef int value_type;

	inline void SetContainer(ContainerPtr obj) { _container = obj; }
	inline ContainerPtr GetContainer() const { return _container; }

private:
	ContainerPtr _container;
};

int main()
{
	DictionaryObject dictionary;
	MixedArrayObject arr;
}
