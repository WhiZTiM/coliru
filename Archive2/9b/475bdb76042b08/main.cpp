#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>

class DiscoveryMessage;
struct Message {
    virtual ~Message() {}
    
    virtual void do_print(std::ostream& os) const { os << "(base)"; }

    friend std::ostream& operator<<(std::ostream& os, Message const& m) {
        m.do_print(os);
        return os;
    }

    template <class Archive> void serialize(Archive &ar, const unsigned int) {
        ar.template register_type<DiscoveryMessage>();
    }
};

class DiscoveryMessage : public Message {
  public:
    DiscoveryMessage() {}

    DiscoveryMessage(int tcpPort) : mTcpReceivePort(tcpPort) {}
    virtual void do_print(std::ostream& os) const {
        os << "{" << mIPAddr << ":" << mTcpReceivePort << "}";
    }

  private:
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, const unsigned int) {
        // invoke serialization of base class (Message)
        ar & boost::serialization::base_object<Message>(*this);
        ar & mTcpReceivePort;
        ar & mIPAddr;
    }

    int mTcpReceivePort;
    std::string mIPAddr = "hello";
};

BOOST_CLASS_EXPORT(Message)
BOOST_CLASS_EXPORT(DiscoveryMessage)

#include <sstream>
#include <iostream>

int main()
{
    std::stringstream ss;
    {
        boost::archive::text_oarchive oa(ss);
        Message * p = new DiscoveryMessage(42);
        oa << p;
    }

    {
        boost::archive::text_iarchive ia(ss);
        Message * p;
        ia >> p;
        std::cout << *p << "\n";
    }
}
