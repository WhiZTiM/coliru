#include <boost/circular_buffer.hpp>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>
#include <stdint.h>


std::vector<uint8_t> generateTestData(unsigned n);
void print(std::string str);
std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec);


struct MakeString
{
    template <typename T>
    MakeString & operator<<(const T & datum);
    MakeString & operator<<(uint8_t n);
    operator std::string() const;
    std::string str() const;
    std::ostringstream mBuffer;
};


template<unsigned Capacity>
struct ConcurrentBuffer
{
    ConcurrentBuffer() :
        read_count_(0),
        write_count_(0),
        buffer_()
    {
    }

    std::size_t capacity() const
    {
        return Capacity;
    }
    
    std::size_t size() const
    {
        return write_count_ - read_count_;
    }

    bool empty() const
    {
        return read_count_ == write_count_;
    }

    std::size_t read(uint8_t* buf, std::size_t len)
    {
        auto max = std::min(len, size());
        for (auto i = 0UL; i != max; ++i)
        {
            *buf++ = buffer_[(read_count_++) % Capacity];
        }
        return max;
    }

    std::size_t write(uint8_t* buf, std::size_t len)
    {
        auto max = std::min(len, Capacity - size());
        for (unsigned i = 0; i != max; ++i)
        {
            buffer_[(write_count_++) % Capacity] = *buf++;
        }
        return max;
    }


    std::atomic<unsigned> read_count_;
    std::atomic<unsigned> write_count_;
    std::array<uint8_t, Capacity> buffer_;
};

namespace {
    
auto dataSize = 2000000UL;
using namespace std::chrono;

}

int main()
{
    ConcurrentBuffer<1514> buf;

    auto testData = generateTestData(dataSize);


    //
    // Reader thread
    //
    std::thread([&] {
        std::vector<uint8_t> readBuffer(testData.size());
        auto numReceived = 0UL;
        while (numReceived != testData.size()) {
            if (auto n = buf.read(&readBuffer[0] + numReceived, readBuffer.size() - numReceived)) {
                numReceived += n;
                //print(MakeString() << " +" << n);
            }
        }
        //assert(testData == readBuffer);
    }).detach();
    
    
    auto startTime = high_resolution_clock::now();


    //
    // Write thread (main thread)
    // 
    auto numWritten = 0UL;
    while (numWritten != testData.size()) {
        if (auto n = buf.write(testData.data() + numWritten, testData.size() - numWritten)) {
            numWritten += n;
            //print(MakeString() << " -" << n);
            if (numWritten == testData.size()) {
                break;
            }
        }
    }
    
    auto elapsed_us = duration_cast<microseconds>(high_resolution_clock::now() - startTime).count();
    std::cout << "SPEED=" << (dataSize / elapsed_us) << std::endl;
}



std::vector<uint8_t> generateTestData(unsigned n)
{
    std::vector<uint8_t> data;
    data.reserve(n);
    while (data.size() != data.capacity())
    {
        data.push_back(data.size());
    }
    return data;
}


//void print(std::string str)
//{
//    static std::mutex fMutex;
//    std::lock_guard<std::mutex> lock(fMutex);
//    std::cout << str << '\n';
//}


inline std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& vec)
{
    for (auto& el : vec)
    {
        os << std::setw(2) << std::setfill('0') << static_cast<int>(el) << ' ';
    }
    return os;
}



template <typename T>
MakeString& MakeString::operator<<(const T & datum)
{
    mBuffer << datum;
    return *this;
}


MakeString& MakeString::operator<<(uint8_t n)
{
    mBuffer << std::setw(2) << std::setfill('0') << static_cast<int>(n) << ' ';
    return *this;
}


MakeString::operator std::string() const
{ return mBuffer.str(); }


std::string MakeString::str() const
{ return mBuffer.str(); }