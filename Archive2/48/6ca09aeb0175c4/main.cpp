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
using Port = std::uint16_t;

    
struct Packet
{    
    nanoseconds timestamp; 
    Port port;
    
    std::tuple<nanoseconds, Port, nanoseconds> priority() const
    {
        // batch size = ~1 microsecond
        return { timestamp / 1024, port, timestamp % 1024 };
    }
};


std::vector<Packet> GetPackets()
{
    std::vector<Packet> result;
    nanoseconds start_time{};
    for (int i = 0; i != num_packets; ++i) // num_packets is defined at in the command line
    {
        result.push_back(Packet {
            start_time += nanoseconds(10 + std::rand() % 20),
            static_cast<Port>(2000 + i % 8)
        });
    }
    return result;
}


int main()
{  
    auto comp = [](const Packet& lhs, const Packet& rhs) {
        return lhs.priority() > rhs.priority();
    };
    
    
    std::priority_queue<Packet, std::vector<Packet>, decltype(comp)> priority_queue(comp);
    
    for (auto& packet : GetPackets())
    {
        std::cout << std::setw(6) << duration_cast<nanoseconds>(packet.timestamp).count() << "ns " << packet.port << "\n";
        priority_queue.push(packet);
    }
    
    while (!priority_queue.empty())
    {
        const Packet& packet = priority_queue.top();
        std::cout << std::setw(6) << duration_cast<nanoseconds>(packet.timestamp).count() << "ns " << packet.port << "\n";
        priority_queue.pop();
    }
}

