#include <boost/lockfree/spsc_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

namespace bip = boost::interprocess;

enum mq_item_type { };
enum log_level_t { };

struct mq_item_t {
    mq_item_type type;

    union
    {
        struct{
            log_level_t level;
            char *      text;
        } log;
        struct{
            char *      control;
            size_t      control_size;
            char *      payload;
            size_t      payload_size;
        } error;
        struct{
            char *      channel;
            char *      control;
            size_t      control_size;
            char *      payload;
            size_t      payload_size;
        } data;
    };
};

namespace {
    static char const* mem_name = "21845989-f5e0-4c84-b170-cd34dc9f37fc";
    static constexpr size_t SHARED_MEMORY_BYTES = 10ul << 20;
}

int main()
{
    typedef bip::managed_shared_memory native_managed_shared_memory;
    typedef boost::interprocess::allocator<mq_item_t, native_managed_shared_memory::segment_manager> shmem_allocator;
    typedef boost::lockfree::spsc_queue<mq_item_t, boost::lockfree::capacity<65535> > lockfree_queue;

    native_managed_shared_memory m_segment(bip::create_only, mem_name, SHARED_MEMORY_BYTES);
    shmem_allocator alloc(m_segment.get_segment_manager());
    auto queue = m_segment.find_or_construct<lockfree_queue>("name of the queue")();
    assert(queue);
}
