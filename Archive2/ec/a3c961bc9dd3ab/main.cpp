#include <iostream>
#include <string>
#include <vector>
struct Message
{
    functype1 open();
    functype2 close();
}

typdef std::shared_ptr<Message> MessagePtr
struct StructuredMessage
{
    bool read(MessagePtr bob)
    {
        //  bind StructureMessage::open to bob.open
        //  bind StructureMessage::close to bob.close
        
    }
    
    void open();
    void close();
}


int main()
{
    // create MessagePtr
    // create StructuredMessage with the source input
    // call StructuredMEssage::read with MessagePtr
    // use MessagePtr
}
