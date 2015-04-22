#include <string>

template<const std::string& V> class TestTmplt
{

};

std::string TEST_REF = "TESTREF" ;

template class TestTmplt<TEST_REF>;

int main()
{}