#include <cstdint>
#include <iostream>
#include <vector>
#include <set>
#include <typeinfo>

template<typename T>
class IObserver
{
public:
    void notify(const T& value)
    {
        try
        {
            onNotification(value);   
        }
        catch(...) {}
    }
    
protected:
    virtual void onNotification(const T& value) = 0;    
};

template<typename T>
class Observable
{
public:
    Observable& subscribe(IObserver<T>* observer)
    {
        observers_.insert(observer);
        return *this;
    }

    Observable& unsubscribe(IObserver<T>* observer)
    {
        observers_.erase(observer);
        return *this;
    }

    Observable& notify(const T& value)
    {
        for (auto o : observers_)
        {
            o->notify(value);
        }
        return *this;
    }

private:
    std::set<IObserver<T>*> observers_;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

struct ZwSendDataReturn
{
    bool value;   
};

struct ZwSendDataCompleted
{
    enum class Status
    {
        Ok,
        NoAck,
        Fail,
        Hop1Fail,
        Hop2Fail,
        Hop3Fail,
        Hop4Fail
    };
    
    Status status;    
};

class ZwSendData 
  : public Observable<ZwSendDataReturn>
  , public Observable<ZwSendDataCompleted>
{
public:
    enum class Options
    {
        LowPower,
        NoRoute,
        Explore,
        Ack
    };

    void operator()(int nodeId, const std::vector<std::uint8_t>& payload, Options options)
    {
        this->Observable<ZwSendDataReturn>::notify(ZwSendDataReturn{true});
        this->Observable<ZwSendDataCompleted>::notify(ZwSendDataCompleted{ZwSendDataCompleted::Status::Ok});
    }
};

template<typename T>
class Printer : public IObserver<T>
{
public:
protected:
    void onNotification(const T& value) override
    {
        std::cout << "Event: " << typeid(T).name() << std::endl;
    }
};

int main(int argc, char* argv[])
{
    ZwSendData sendData{};
    
    Printer<ZwSendDataReturn> p1{};
    Printer<ZwSendDataCompleted> p2{};
    
    sendData.Observable<ZwSendDataReturn>::subscribe(&p1);
    sendData.Observable<ZwSendDataCompleted>::subscribe(&p2);
    
    sendData(16, {0xdd, 0xee, 0xff}, ZwSendData::Options::Ack);
    
    return 0;
}
