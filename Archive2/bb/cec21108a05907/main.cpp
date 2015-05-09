    #include <utility>
    #include <boost/any.hpp>

    std::pair< int, boost::any > y;
    void test()
    {
      y = std::pair< int, boost::any >( 1, 2 ); // error!
    }
    
    int main() {}