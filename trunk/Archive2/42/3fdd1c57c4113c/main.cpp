#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using uint = std::uint32_t;

    class RangeAllocator
    {
    public:
        struct Range {
            uint start;
            uint size;
        };

        uint const m_block_size;
        std::vector<Range> m_list_avail;

        RangeAllocator(uint block_size) :
            m_block_size(block_size)
        {
            m_list_avail.push_back({0,m_block_size});
        }

        void Reserve(uint size)
        {
            m_list_avail.reserve(size);
        }

        Range AcquireRange(uint size)
        {
            for(auto range_it = m_list_avail.begin();
                range_it != m_list_avail.end(); ++range_it)
            {
                if(range_it->size > size)
                {
                    // split the range
                    Range range_used{
                        range_it->start,
                        size
                    };

                    Range range_keep{
                        range_it->start+size,
                        range_it->size-size
                    };

                    m_list_avail.erase(range_it);

                    // ordered insert of split range
                    listAvailOrderedInsert(m_list_avail,range_keep);
                    return range_used;
                }
                else if(range_it->size == size)
                {
                    // no need to split the range,
                    // just move it to the used list
                    Range range = *range_it;
                    m_list_avail.erase(range_it);
                    return range;
                }
            }

            return Range{0,0};
        }

        void ReleaseRange(Range const &range)
        {
            listAvailOrderedInsert(m_list_avail,range);
        }

        static void listAvailOrderedInsert(std::vector<Range> &list_avail,
                                           Range const &range)
        {
            auto it = std::upper_bound(
                        list_avail.begin(),
                        list_avail.end(),
                        range,
                        [](Range const &a, Range const &b){
                            return (a.start < b.start);
                        });

            if(it != list_avail.end())
            {
                // it points to a range with a start value
                // greater than @range

                // see if we can merge with the next range
                if(it->start == (range.start+range.size)) {
                    // we can merge with the next range (it)
                    it->start = range.start;
                    it->size += range.size;

                    // see if we can merge with the preceding range
                    if(it != list_avail.begin()) {
                        auto it_prev = std::prev(it);
                        if(it->start == (it_prev->start+it_prev->size)) {
                            // we can merge with the prev range (it_prev)
                            it->start = it_prev->start;
                            it->size += it_prev->size;

                            list_avail.erase(it_prev);
                        }
                    }
                }
                // see if we can merge with the preceding range
                else if(it != list_avail.begin()) {
                    auto it_prev = std::prev(it);
                    if(range.start == (it_prev->start+it_prev->size)) {
                        // we can merge with the prev range (it_prev)
                        it_prev->size += range.size;
                    }
                }
                else {
                    // can't merge
                    list_avail.insert(it,range);
                }
            }
            else {
                list_avail.insert(it,range);
            }
        }
    };