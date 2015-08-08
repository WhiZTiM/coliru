#include <atomic>
#include <cstddef>

template<typename T, size_t size>
struct RingBuffer {
    RingBuffer() : ahead(0), atail(0) {}

    bool push(const T& value) {
        size_t head = ahead.load(std::memory_order_relaxed);
        size_t next_head = next(head);
        if (next_head == atail.load(std::memory_order_acquire)) return false;
        ring_[head] = value;
        ahead.store(next_head, std::memory_order_release);
        return true;
    }

    bool pop(T& value) {
        size_t tail = atail.load(std::memory_order_relaxed);
        if (tail == ahead.load(std::memory_order_acquire)) return false;
        value = ring_[tail];
        atail.store(next(tail), std::memory_order_release);
        return true;
    }

private:
    size_t next(size_t current) { return (current + 1) % size; }
    T ring_[size];
    std::atomic<size_t> ahead, atail;
};

RingBuffer<int, 32> buf;
bool push(int x) { return buf.push(x); } // Just to generate assembly.
bool pop(int& x) { return buf.pop(x); } // Just to generate assembly.