#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>


using Clock = std::chrono::high_resolution_clock;
using Microseconds = std::chrono::microseconds;


struct Packet
{
    int muxid;
    std::size_t seqnum;
};


std::vector<Packet> packets;


int main()
{
    enum { capacity = 10 * 1000 };

    packets.reserve(capacity);
    for (auto i = 0; i != capacity; ++i)
    {
        packets.push_back({ static_cast<int>(random() % 10), packets.size() });
    }


    auto start_time = Clock::now();

    //struct Predicate
    //{
        //Predicate(int muxid) : muxid(muxid) {}
        //bool operator()(const Packet& packet) const
        //{
            //return packet.muxid < muxid;
        //}
        //int muxid;
    //};

    auto b = packets.begin(), e = packets.end();   //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(0)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(1)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(2)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(3)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(4)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(5)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(6)); //std::cout << "remaining=" << (e - b) << '\n';
    //b = std::stable_partition(b, e, Predicate(7)); //std::cout << "remaining=" << (e - b) << '\n';
    std::stable_sort(b, e, [](const Packet& lhs, const Packet& rhs) { return lhs.muxid < rhs.muxid; });

    auto elapsed_time = Clock::now();


    auto elapsed = std::chrono::duration_cast<Microseconds>(elapsed_time - start_time).count();
    std::cout << elapsed << "us" << std::endl;

    for (auto& p : packets) std::cout << p.muxid << ' ' << p.seqnum << '\n';
}
