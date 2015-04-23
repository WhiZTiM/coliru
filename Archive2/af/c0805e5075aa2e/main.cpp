
struct TCPDecoder
{
};

struct ReceivedData
{
};

struct Packet
{
};



struct TCP
{
    template<typename LLP>
    TCP(LLP& llp) : mLLP(&llp), mControllerFunction(&Controller<LLP>)
    {
        
    }
    
    void receive(const ReceivedData& data)
    {
        mControllerFunction(*this, mLLP, (void*)&data);
    }
    
    void send(Packet& packet)
    {
        mControllerFunction(*this, mLLP, &packet);
    }
    
    template<typename LLDec>
    void receive(const TCPDecoder& tcpdec, const LLDec& lldec)
    {
        if (!validate(tcpdec, lldec))
        {
            return;
        }
    }
    
private:
    enum Operation { Receive, Send };
    
    template<typename LLP>
    static void Controller(TCP& tcp, Operation op, void* llp_ptr, void* arg_ptr)
    {        
        auto& llp = *static_cast<LLP*>(llp_ptr);
        
        switch (op)
        {
            case Receive:
            {
                using LLDec = typename LLP::Decoder;
                tcp.receive(llp, LLDec(*static_cast<ReceivedData*>(arg_ptr)));
                break;
            }
            case Send:
            {
                llp.send(*static_cast<Packet*>(arg_ptr));
                break;
            }
        }
    }
    
    using ControllerFunction = void (*) (TCP&, void*, void*);
    ControllerFunction mControllerFunction;
    void* mLLP;
};
