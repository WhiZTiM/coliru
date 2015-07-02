#include <iostream>

struct iMessage{};
struct Message:iMessage{};

template <class msg_t=iMessage>
class Client
{
public:
  void tick(void){ msg_t m;recv_callback(m); }
protected:
  virtual void recv_callback(const msg_t& m){}
};

template <class msg_t=iMessage>
class Worker : public Client<msg_t>
{

protected:
  void recv_callback(const msg_t& m) /*override*/
    {std::cerr<<"no one calls me\n";}
};

int main() {
  Worker<Message/*inherits from iMessage*/> w;
  w.tick();// is calling Client::recv_callback
           // instead of Worker::recv_callback :(
}
