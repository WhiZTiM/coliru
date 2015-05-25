#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
 
 template<typename It>
void print_subrange(It first, It last, It subfirst, It sublast) {
    It c = first;
    for( ; c!=subfirst; ++c)
        std::cout << ' ' << *c;
    std::cout << '|';
    if (subfirst != last)
        std::cout << *c;
    for(++c ; c!=sublast; ++c)
        std::cout << ' ' << *c;
    std::cout << '|';
    for( ; c!=last; ++c)
        std::cout << *c << ' ';
    std::cout << '\n';
}
 
 template <class BidiIter, class CompatitorType>
 void NotQuickSort(BidiIter first, BidiIter last, CompatitorType&& comparitor)
 {
    if(first==last) return;
    //move the maximum element to the front
    BidiIter max_it = std::max_element(first,last,comparitor);
    if (max_it != first)
        std::iter_swap(first, max_it);
    BidiIter cur_begin = first;
    BidiIter cur_end = last;
    //current state is a large element A followed by a bunch of elements less than or equal to A. (I call this a "chunk")
    //After this may be a larger element B followed by a bunch of elements greater than A but less than or equal to B.
    //etc etc until the end of the data
    while(cur_begin != last) {
        //if we don't know where the end of the current chunk is, simply search for the first element greater than the first element
        BidiIter pivot_it = std::next(cur_begin);
        if (cur_begin == cur_end) {
            auto&& max_value = *cur_begin;
            cur_end = std::find_if(pivot_it, last, [&comparitor,&max_value](const auto& e){return comparitor(max_value,e);});
        }
        //print_subrange(first, last, cur_begin, cur_end); //DEBUGGING PRINT HERE
        //if the chunk only has the "large" element, skip to the next chunk.
        //(cur_end ends up beingn equal to cur_begin, which triggers a search for the end)
        if (pivot_it == cur_end) {
            ++cur_begin;
            continue;
        }
        //if the chunk has a "large" element followed by one other element less than or equal to it, swap them and skip to the next chunk
        //(cur_end ends up beingn equal to cur_begin, which triggers a search for the end)
        BidiIter subrange_begin = std::next(pivot_it);
        if (subrange_begin == cur_end) {
            std::iter_swap(cur_begin, pivot_it);
            ++cur_begin;
            ++cur_begin;
            continue;
        }
        //here's the "recursive" step.  We're going to split the "less than or equal" elements into two chunks.
        //the first element, A, is the largest in this chunk, and will be the "large" element for the right half.
        //we're going to pick the second element, B, to be our pivot, and thus our large element for the left half.
        //so partition the "smaller" elements based on the value of B, the pivot.
        auto&& pivot_value = *pivot_it;
        BidiIter mid = std::partition(subrange_begin, cur_end,  [&comparitor,&pivot_value](const auto& e){return !comparitor(pivot_value,e);});
        //we're going to want B to be the first element, so swap A and B
        std::iter_swap(cur_begin, pivot_it);
        //if no elements are less than B, then A (at it's new position) to the end of the chunk is our next chunk
        if (subrange_begin == mid) {
            ++cur_begin;
            continue;
        }
        //otherwise, swap A to the middle of the partition.  
        --mid;
        std::iter_swap(pivot_it, mid);
        //now it's [B][Elements less than or equal to B][A][Elements greater than B but less than or equal to A][C][Elements greater than A but less than or equal to C]
        //so we simply continue, operating on the B chunk, whcih ends at the partition point.
        cur_end = mid;
    }
 }
 template <class BidiIter>
 void NotQuickSort(BidiIter first, BidiIter last)
 {return NotQuickSort(first,last,std::less<void>());}
 template <class Container, class CompatitorType>
 void NotQuickSort(Container& c, CompatitorType&& comparitor)
 {return NotQuickSort(std::begin(c), std::end(c), comparitor);}
 template <class Container>
 void NotQuickSort(Container& c)
 {return NotQuickSort(std::begin(c), std::end(c), std::less<void>());}


void TestNotQuickSort(std::vector<int> c) {
    NotQuickSort(c.begin(), c.end(), std::less<int>{});
    assert(std::is_sorted(c.begin(), c.end()));        
}
int main() {
    TestNotQuickSort({});
    TestNotQuickSort({0});
    TestNotQuickSort({0, 0});
    TestNotQuickSort({0, 1});
    TestNotQuickSort({1, 0});
    TestNotQuickSort({0, 0, 0});
    TestNotQuickSort({0, 0, 1});
    TestNotQuickSort({0, 1, 0});
    TestNotQuickSort({1, 0, 0});
    TestNotQuickSort({0, 1, 1});
    TestNotQuickSort({1, 0, 1});
    TestNotQuickSort({1, 1, 0});
    TestNotQuickSort({0, 1, 2});
    TestNotQuickSort({0, 2, 1});
    TestNotQuickSort({1, 0, 2});
    TestNotQuickSort({1, 2, 0});
    TestNotQuickSort({2, 0, 1});
    TestNotQuickSort({2, 1, 0});
    std::cout << "PASS";
}
