#include <cstdint>
#include <type_traits>

class IHostMediaAccessControl {};

template<std::uint8_t Id, typename R>
class Generic : public Observable<R>
{
public:
    using ReturnType = R;
    
    Generic(IHostMediaAccessControl& hmac) : hmac_{hmac}
    {
        hmac.on<FrameReceived>([this](const auto& event)
        {
            if (event.frame == SofFrame::Type::Response)
            {
                this->notify(R{}); // <--- na razie wystarczy tylko tyle
            }
        });
    }
    
    template<typename FusionSequence>
    void operator()(const FusionSequence& sequence)
    {
        std::vector<std::uint8_t> payload{};        
        payload.push_back(Id);
        fusion::for_each(sequence, [&payload](const auto& v)
        {
            using Fibaro::serialize; // <--- customization point
            serialize(std::back_inserter(payload), v);
        });
        payload.push_back(1); // <--- function identifier, na razie wystarczy stała "1"
        hmac_.onSendFrame(SofFrame{SofFrame::Type::Request, std::move(payload)});
    }
    
private:
    IHostMediaAccessControl& hmac_;
};

int main(int argc, char* argv[])
{
    
    return 0;
}
