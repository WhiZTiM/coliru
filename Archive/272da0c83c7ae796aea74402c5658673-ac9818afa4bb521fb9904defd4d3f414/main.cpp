//#include <iostream>

#define TRACE //std::cout << __PRETTY_FUNCTION__ << std::endl;

// your enum
enum: unsigned
{
    fin = (1 << 0),
    syn = (1 << 1),
    ack = (1 << 4)
    // etc...
};


// this replaces your individual receive types:
template<unsigned> struct receive {};

struct state_machine_type
{    
    template<typename T>
    void process_event(T t);
};


// this is the magic translation to compile time
template<unsigned bit = 1, unsigned mask = fin|syn|ack, unsigned value = 0>
struct call
{
    void process(state_machine_type& state_machine, unsigned flags)
    {
        TRACE
        if (flags & bit)
        {
            call<(bit << 1), mask & ~bit, value | bit>{}.process(state_machine, flags);
        }
        else
        {
            call<(bit << 1), mask & ~bit, value>{}.process(state_machine, flags);
        }
    }
};


template<unsigned bit, unsigned value>
struct call<bit, 0, value>
{
    void process(state_machine_type& state_machine, unsigned)
    {
        TRACE
        state_machine.process_event(receive<value>{});
    }
};

unsigned get_runtime_value();

int main()
{
    state_machine_type state_machine;
    call<>{}.process(state_machine, get_runtime_value());
}