#include <boost/lockfree/spsc_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/variant.hpp>
#include <boost/range.hpp>
#include <string>
#include <iostream>

namespace bip = boost::interprocess;
using boost::lockfree::spsc_queue;

#ifdef COLIRU
typedef bip::managed_mapped_file msm_t;
#else
typedef bip::managed_shared_memory msm_t;
#endif

namespace mq {
    enum log_level_t { default_level };

    typedef boost::interprocess::allocator<char, msm_t::segment_manager> char_alloc;
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, char_alloc> shmem_string;
    typedef boost::interprocess::vector<char, char_alloc> shmem_blob;

    using boost::begin;
    using boost::end;

    struct log {
        typedef char_alloc allocator_type;

        log(char_alloc alloc) : text(alloc) {}
        log(log_level_t level, const char* txt, char_alloc alloc) : level(level), text(txt, alloc) { };

        log_level_t level;
        shmem_string text;
    };

    struct error {
        typedef char_alloc allocator_type;

        error(char_alloc alloc) : control(alloc), payload(alloc) {}

        template <typename Ctl, typename Payload>
        error(Ctl const& ctl, Payload const& pl, char_alloc alloc) 
            : control(begin(ctl), end(ctl), alloc),
              payload(begin(pl), end(pl), alloc)
        { }

        shmem_blob control, payload;
    };

    struct data {
        typedef char_alloc allocator_type;

        data(char_alloc alloc) : channel(alloc), control(alloc), payload(alloc) {}

        template <typename Ctl, typename Payload>
        data(char const* channel, Ctl const& ctl, Payload const& pl, char_alloc alloc) 
            : channel(channel, alloc),
              control(begin(ctl), end(ctl), alloc),
              payload(begin(pl), end(pl), alloc)
        { }

        shmem_string channel;
        shmem_blob control, payload;
    };

    typedef boost::variant<log, error, data> item_t;
}

namespace {
    static char const* mem_name = "21845989-f5e0-4c84-b170-cd34dc9f37fc";
    static constexpr size_t SHARED_MEMORY_BYTES = 10ul << 20;
}

int main()
{
    typedef boost::interprocess::allocator<mq::item_t, msm_t::segment_manager> shmem_allocator;
    typedef boost::lockfree::spsc_queue<mq::item_t, boost::lockfree::capacity<65535> > lockfree_queue;

    msm_t m_segment(bip::create_only, mem_name, SHARED_MEMORY_BYTES);
    shmem_allocator alloc(m_segment.get_segment_manager());

    auto queue = m_segment.find_or_construct<lockfree_queue>("name of the queue")();

    queue->push(mq::error("control", "payload", alloc));
    queue->push(mq::data("channel", "control", "payload", alloc));
    queue->push(mq::log(mq::default_level, "text", alloc));
}
