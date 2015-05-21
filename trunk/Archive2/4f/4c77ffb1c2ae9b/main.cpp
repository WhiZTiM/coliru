
// A generic message passing system (a.k.a. Mediator).  Application-specific message types 
//  and handlers for those message types can be add added without modification to this library.
//  Thus, it is generic.  When using the Mediator to publish a message, the subscribed message
//  handlers are dynamically type-checked, and the message is passed to those handlers who
//  are of the correct type (implement the appropriate message handler abstract base class).

// For a detailed explanation of this messaging system's design, see the article it was 
//  inspired by at:
//      http://www.drdobbs.com/cpp/message-handling-without-dependencies/184429055?pgno=1
//  ...making sure to understand the "gotchas!"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// LIBRARY-PROVIDED:

// Message handler base class.
class MessageHandlerBase
{
    protected:
        virtual ~MessageHandlerBase() { }
};

// Message handler abstract base class, templated on Message type.
template <class MessageT>
class MessageHandler : public virtual MessageHandlerBase
{
    public:
        virtual void receive(MessageT const * const p_message) = 0;
        
    protected:
        virtual ~MessageHandler() { }
};

// Mediator/message-center/post-office class.
class Mediator
{
    public:
        template <class MessageT>
        void publish(MessageT const * const p_message)
        {
            for_each(message_handlers_.begin(), message_handlers_.end(), 
                [p_message](MessageHandlerBase *p_message_handler)
                {
                    MessageHandler<MessageT> *p_derived_message_handler = dynamic_cast< MessageHandler<MessageT> * >(p_message_handler);
                    if(p_derived_message_handler != NULL)
                    {
                        p_derived_message_handler->receive(p_message);
                    }
                }
            );
        }
        
        void subscribe(MessageHandlerBase *p_message_handler)
        {
            message_handlers_.push_back(p_message_handler);
        }
        
    private:
        vector< MessageHandlerBase * > message_handlers_;
};


// APPLICATION-PROVIDED

// Arbitrary message base class.
class Message
{

};

// Arbitrary message classes.
class Message1 : public Message
{
    public:
        Message1() : data(10) { }
        int data;
};

class Message2 : public Message
{
    public:
        Message2() : data('c') { }
        char data;
};

// Arbitrary concrete message handling classes.
class Foo : public MessageHandler<Message1>
{
    public:
        Foo() : foo_num(++foo_count)
        {
            cout << "Foo number " << foo_num << " created." << endl;
        }
        
        void receive(Message1 const * const p_message)
        {
            cout << "foo" << foo_num << ".receive():  Message1 received.  It says " << p_message->data << "." << endl;
        }
        
    private:
        static int foo_count;
        const int foo_num;
};
int Foo::foo_count = 0;

class Bar : public MessageHandler<Message2>
{
    public:
        Bar() : bar_num(++bar_count)
        {
            cout << "Bar number " << bar_num << " created." << endl;
        }
        
        void receive(Message2 const * const p_message)
        {
            cout << "bar" << bar_num << ".receive():  Message2 received.  It says " << p_message->data << "." << endl;
        }

    private:
        static int bar_count;
        const int bar_num;
};
int Bar::bar_count = 0;

class FooBar : public MessageHandler<Message1>, public MessageHandler<Message2>
{
    public:
        FooBar() : foobar_num(++foobar_count)
        {
            cout << "FooBar number " << foobar_num << " created." << endl;
        }
    
        void receive(Message1 const * const p_message)
        {
            cout << "foobar" << foobar_num << ".receive():  Message1 received.  It says " << p_message->data << "." << endl;
        }
        
        void receive(Message2 const * const p_message)
        {
            cout << "foobar" << foobar_num << ".receive():  Message2 received.  It says " << p_message->data << "." << endl;
        }
        
    private:
        static int foobar_count;
        const int foobar_num;
};
int FooBar::foobar_count = 0;

int main()
{
    Foo foo1, foo2, foo3;
    Bar bar1, bar2, bar3;
    FooBar foobar1;
    
    Mediator mediator;
    mediator.subscribe(&foo1);
    mediator.subscribe(&foo2);
    mediator.subscribe(&foo3);
    
    mediator.subscribe(&bar1);
    mediator.subscribe(&bar2);
    mediator.subscribe(&bar3);
    
    mediator.subscribe(&foobar1);
    
    Message1 *p_msg1 = new Message1();
    mediator.publish(p_msg1);
    delete p_msg1;
    
    Message2 *p_msg2 = new Message2();
    mediator.publish(p_msg2);
    delete p_msg2;
}