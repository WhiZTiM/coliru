#include <iostream>

class foo
{
public:
    void setIsNewClient ( bool isnewclient ) { _isNewClient = isnewclient; }
    bool getIsNewClient ( ) { return _isNewClient; }
 
private:
    bool _isNewClient;
};

int main()
{
    foo x;
    x.setIsNewClient(true);
    std::cout << x.getIsNewClient() << std::endl;
    x.setIsNewClient(false);
    std::cout << x.getIsNewClient() << std::endl;
}
