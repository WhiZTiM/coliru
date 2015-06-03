#include <vector>
#include <functional>
#include <iostream>
#include <stdio.h>

template <typename T> struct TypeName
{
    static std::string get()
	{
		std::string fullName=typeid(T).name();

		size_t beginPos=0;
		size_t classPos=fullName.find("class");
		size_t nameSpacePos=fullName.find_last_of("::");

		if(classPos != std::string::npos)
			beginPos=classPos+6;
		if(nameSpacePos != std::string::npos)
		{
			if(nameSpacePos+1 > beginPos)
				beginPos=nameSpacePos+1;
		}
		return fullName.substr(beginPos);
	}
};

struct InterfaceType
{
	InterfaceType():id(-1) {}

	unsigned int id;
	std::vector<unsigned int> idInheritance;
	std::string name;
};

template <typename T>
struct has_s_type
{
	struct Fallback { InterfaceType s_type; };
	struct Derived: T, Fallback {};

	template<typename C, C> struct ChT;
	template<typename C> static char(&f(ChT<InterfaceType Fallback::*, &C::s_type>*))[1];
	template<typename C> static char(&f(...))[2];

	static bool const value=sizeof(f<Derived>(0)) == 2;
};



class BaseInterface
{
public:
	BaseInterface() {}
	virtual ~BaseInterface() {}
};

class TestCase
{
public:
	TestCase() {}
	virtual ~TestCase() {}

	//	static InterfaceType s_type;
	static InterfaceType s_type;
};

class TestCase2:public TestCase
{
public:
	TestCase2() {}
	virtual ~TestCase2() {}

};

template<typename CLASS, typename INTERFACE>
class AutoRegister:public INTERFACE
{
public:
	AutoRegister():INTERFACE() { &s_type; }

	static BaseInterface *create(unsigned int type) { CLASS *newClass=new CLASS(); return newClass; }
	
	template<typename T, bool=false>
	struct BaseId
	{
		static std::vector<unsigned int> get() { return std::vector<unsigned int>(); }
	};

	template<typename T>
	struct BaseId<T, true>
	{
		static std::vector<unsigned int> get()
		{ 
			std::vector<unsigned int> ids;
			ids.push_back(INTERFACE::s_type.id); ids.insert(ids.end(), INTERFACE::s_type.idInheritance.begin(), INTERFACE::s_type.idInheritance.end());
			return ids;
		}
	};
	
	static std::vector<unsigned int> getBaseIds() { return BaseId<INTERFACE, has_s_type<INTERFACE>::value>::get(); }

	//	static std::vector<unsigned int> getBaseIds() { return BaseId<INTERFACE>::get<INTERFACE>(); }
	
public:
	static const InterfaceType s_type;

};

class InterfaceFactory
{
public:
	typedef BaseInterface *(*FactoryFunc)(unsigned int type);
	class BaseInterfaceNode
	{
	public:
		BaseInterfaceNode(unsigned int type, std::string typeName, FactoryFunc factoryFunction):
			m_type(type), m_typeName(typeName), m_factoryFunction(factoryFunction)
		{};

		size_t type() { return m_type; }
		std::string typeName() { return m_typeName; }
		BaseInterface *factoryFunction() { return m_factoryFunction(m_type); }

	private:
		unsigned int m_type;
		std::string m_typeName;
		FactoryFunc m_factoryFunction;
	};
	typedef std::vector<BaseInterfaceNode> BaseInterfaceNodes;

public:
	InterfaceFactory() {}
	~InterfaceFactory() {}

public:
	static BaseInterface *createType(unsigned int type);
	static InterfaceType registerType(std::string typeName, std::vector<unsigned int> ids, FactoryFunc factoryFunc);

	struct BaseInterfaceNodeHolder
	{
		BaseInterfaceNodeHolder():s_interfaceTypeIndex(0) {}

		BaseInterfaceNodes s_baseInterfaceNodes;
		unsigned int s_interfaceTypeIndex;
	};

private:
};

template<typename CLASS, typename INTERFACE> const InterfaceType AutoRegister<CLASS, INTERFACE>::s_type=\
InterfaceFactory::registerType(TypeName<CLASS>::get(), AutoRegister<CLASS, INTERFACE>::getBaseIds(), &AutoRegister<CLASS, INTERFACE>::create);

InterfaceFactory::BaseInterfaceNodeHolder *s_nodes=nullptr;

InterfaceType InterfaceFactory::registerType(std::string typeName, std::vector<unsigned int> ids, FactoryFunc factoryFunc)
{
	if(s_nodes == nullptr)
		s_nodes=new BaseInterfaceNodeHolder();

	InterfaceType sampleType;

	sampleType.id=s_nodes->s_interfaceTypeIndex;
	sampleType.idInheritance=ids;
	sampleType.name=typeName;

	s_nodes->s_baseInterfaceNodes.push_back(BaseInterfaceNode(s_nodes->s_interfaceTypeIndex, typeName, factoryFunc));
	s_nodes->s_interfaceTypeIndex++;
	return sampleType;
}

class Base:public AutoRegister<Base, BaseInterface>
{};

class Derived:public AutoRegister<Derived, Base>
{};

int main(int argc, const char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << has_s_type<TestCase>::value << std::endl;
	std::cout << has_s_type<TestCase2>::value << std::endl;
	std::cout << has_s_type<BaseInterface>::value << std::endl;
	std::cout << has_s_type<Base>::value << std::endl;
	std::cout << has_s_type<Derived>::value << std::endl;

	std::cout << std::endl;

	std::cout << "Base:" << std::endl;
	std::cout << Base::s_type.id;
	for(unsigned int id: Base::s_type.idInheritance)
		std::cout << ", " << id;
	std::cout << std::endl;

	std::cout << "Derived:" << std::endl;
	std::cout << Derived::s_type.id;
	for(unsigned int id: Derived::s_type.idInheritance)
		std::cout << ", " << id;
	std::cout << std::endl;
}