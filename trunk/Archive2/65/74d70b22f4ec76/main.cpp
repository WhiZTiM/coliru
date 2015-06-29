#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

class printer
{
public:
    printer(boost::asio::io_service& io)
        : timer_(io, boost::posix_time::seconds(1)),
          count_(0)
    {
        timer_.async_wait(boost::bind(&printer::print, this, boost::asio::placeholders::error));
    }
    ~printer()
    {
        std::cout << "Final count is " << count_ << "\n";
    }

    void print(boost::system::error_code const ec)
    {
        if (ec)
            std::cout << "Error: " << ec.message() << "\n";
        if (count_ < 5)
        {
            std::cout << count_ << "\n";
            ++count_;

            timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this, boost::asio::placeholders::error));
        }
    }

private:
    boost::asio::deadline_timer timer_;
    int count_;
};

int main()
{
    boost::asio::io_service io;
    printer p(io);
    io.run();
}
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using MainKey      = uint64_t;
using SecondaryKey = uint64_t;
using Data         = std::string;

struct RecordKey
{
    MainKey         mainKey;
    SecondaryKey    secondaryKey;

    RecordKey( const MainKey mainKey, SecondaryKey secondaryKey):
        mainKey( mainKey),
        secondaryKey( secondaryKey)
    {}
};

struct Record: public RecordKey
{
    Data data;

    Record( const MainKey mainKey = 0, const SecondaryKey secondaryKey = 0, const Data& data = 0):
        RecordKey( mainKey, secondaryKey),
        data( data)
    {}

    friend std::ostream& operator<<(std::ostream& os, Record const& r) {
        return os << " Record[" << r.mainKey << ", " << r.secondaryKey << ", " << r.data << "]";
    }
};

struct MainKeyTag {};
struct SecondaryKeyTag {};
struct CompositeKeyTag {};

using boost::multi_index_container;
using namespace boost::multi_index;

typedef boost::multi_index_container<
    Record,
    indexed_by<
        hashed_unique< tag<CompositeKeyTag>, 
        composite_key<Record, 
                    member<RecordKey, MainKey, &RecordKey::mainKey>,
                    member<RecordKey, SecondaryKey, &RecordKey::secondaryKey>
    > > > > RecordContainer;


int main()
{
    RecordContainer records;
    records.insert(Record(10, 20, "12"));
    records.insert(Record(10, 30, "13"));
    records.insert(Record(10, 30, "13 - needs to be unique!"));
    records.insert(Record(30, 40, "34"));
    records.insert(Record(30, 50, "35"));
    records.insert(Record(50, 60, "56"));
    records.insert(Record(50, 70, "57"));
    records.insert(Record(70, 80, "78"));

    std::cout << "\nAll records:\n----------------------------------------------------------------------\n";
    for (auto const& r : records)
        std::cout << r << "\n";

    std::cout << "\nAll records with (main,secondary) == (10,30):\n----------------------------------------------------------------------\n";
    auto& index = records.get<0>();
    auto found = index.find(boost::make_tuple(10,30));
    if (found != index.end())
        std::cout << *found << "\n";
}