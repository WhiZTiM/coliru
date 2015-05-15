#include <boost/fusion/include/list.hpp>
#include <tuple>

struct XMLDeclarationElement
{
    XMLDeclarationElement(std::string){}	
};
struct SignatureXMLElement
{
	SignatureXMLElement(std::string){}	
};

template<typename... ITEM_TYPES>
using List = boost::fusion::list<ITEM_TYPES...>;

template <typename T, typename Tuple, std::size_t... Indices>
T construct_single (std::index_sequence<Indices...>, Tuple&& t)
{
	return T(std::get<Indices>(std::forward<Tuple>(t))...);	
}

template <typename... Types, typename... Tuples>
List<Types...> construct_list (Tuples&&... ts)
{
	return {construct_single<Types>
	          (std::index_sequence_for<Tuples>{}, std::forward<Tuples>(ts))...};
}

template<typename... CHILDREN_TYPES>
class ElementContainer 
{ 
protected:
    const List<CHILDREN_TYPES...> children;
public:
     ElementContainer(CHILDREN_TYPES&&... args) : children(std::forward<CHILDREN_TYPES>(args)...) {}
     
     template <typename... Tuples>
     ElementContainer(std::piecewise_construct_t, Tuples&&... args) 
         : children(construct_list<CHILDREN_TYPES...>(std::forward<Tuples>(args)...)) {}
};



class XMLSignatureDocument : public ElementContainer<XMLDeclarationElement, SignatureXMLElement>
{
public:
    XMLSignatureDocument() :ElementContainer(
    	std::piecewise_construct,
        std::forward_as_tuple("<?xml version=\"1.0\" encoding=\"utf-8\"?>"),
        std::forward_as_tuple("<Signature xmlns=\"http://www.w3.org/2000/09/xmldsig#\"></signature>"
        )) {};
};

int main()
{
	
}