#include <array>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <type_traits>
#include <vector>


using namespace std::chrono;
using Clock = high_resolution_clock;
using Nanoseconds = nanoseconds;
using Milliseconds = milliseconds;
using Microseconds = microseconds;
using Port = std::uint16_t;
using ProtocolId = std::uint8_t;
using IPv4 = std::array<std::uint8_t, 4>;
using Timestamp = Nanoseconds;

    
struct Packet
{    
    Nanoseconds timestamp; 
    
    Port port;
    
    std::tuple<Nanoseconds, Port, Nanoseconds> priority() const
    {
        return { timestamp / 1000, port, timestamp % 1000 };
    }
};


std::vector<Packet> packets = []
{
    std::vector<Packet> result;
    Nanoseconds start_time{};
    for (int i = 0; i != NUM_PACKETS; ++i)
    {
        result.push_back(Packet {
            start_time += Nanoseconds(10 + std::rand() % 10),
            static_cast<Port>(2000 + i % 8)
        });
    }
    return result;
}();


int main()
{  
    
    auto comp = [](const Packet& lhs, const Packet& rhs)
    {
        return lhs.priority() > rhs.priority();
    };
    
    std::priority_queue<Packet, std::vector<Packet>, decltype(comp)> priority_queue(comp);
    
    auto start = Clock::now();
    for (auto& packet : packets)
    {
        priority_queue.push(packet);
    }
    auto elapsed = (duration_cast<nanoseconds>(Clock::now() - start).count());
    std::cerr << "demultiplexing overhead: " << int(0.5 + 1.0 * elapsed / packets.size()) << " ns/packet\n\n";
        
        
    for (auto& packet : packets)
    {
        std::cout << std::setw(6) << duration_cast<Nanoseconds>(packet.timestamp).count() << "ns " << packet.port << "\n";
    }
    
    while (!priority_queue.empty())
    {
        const Packet& packet = priority_queue.top();
        std::cout << std::setw(6) << duration_cast<Nanoseconds>(packet.timestamp).count() << "ns " << packet.port << "\n";
        priority_queue.pop();
    }
}

