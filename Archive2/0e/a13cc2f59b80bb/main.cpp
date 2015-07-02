#include <iostream>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/vector.hpp>

namespace svt
{
    //Layer types have don't share a base class but are required
    // to expose Layer::options (even if it's an empty class)
    
    //encryption layer
    struct encrypt { struct options { bool buggy = true; }; };

    //routing layer
    struct route { struct options { int ttl = 42; }; };
    
    //ordering layer
    struct ordered { struct options { int window = 4; }; };
    
    namespace detail
    {
        template <class T> struct opts { typedef typename T::options type; };
    }


    template <class... Layers>
    class flow
    {
      public:
        typedef typename boost::mpl::inherit_linearly<
            boost::mpl::vector<Layers...>,
            boost::mpl::inherit<typename boost::mpl::_1, detail::opts<boost::mpl::_2>>
        >::type options;

    };
}

int main(int argc, char *argv[])
{
    typedef svt::flow<svt::route, svt::encrypt, svt::ordered> myflow;
    typename myflow::options opts; //default construct
    
    std::cout << std::boolalpha << opts.buggy  << " " 
                                << opts.ttl    << " " 
                                << opts.window << std::endl;
}
