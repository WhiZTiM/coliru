#include <utility>

struct Item
{
    Item() {}
    Item(Item&&) { not_defined(); }
    Item(const Item&) { not_defined(); }
    
    void not_defined();
    
    void bla(){}
    
    char rather_big[128];
};

Item get()
{
    return Item();
}

int main()
{   
    Item item(get()); // ok
    
    // linker error
    //Item item2(std::move(item)); 
}