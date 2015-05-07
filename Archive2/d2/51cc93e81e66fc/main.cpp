#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <type_traits>

template <typename T, size_t MaxN, typename _Pred = std::less<T>>
class binary_heap
{
  size_t heap_size;
  T elements[MaxN];
  _Pred pred;
public:
  binary_heap() : heap_size( 0 ) {}

  typedef const T & const_reference;
  typedef T value_type;

private:
  void sift_down( size_t pos )
  {
    while ( pos < heap_size )
    {
      size_t child1_pos = 2 * pos + 1;
      size_t child2_pos = 2 * pos + 2;

      if ( child1_pos >= heap_size ) child1_pos = 0;
      if ( child2_pos >= heap_size ) child2_pos = 0;

      if ( child1_pos && child2_pos )
      {
        if ( pred(elements[child1_pos], elements[child2_pos]) )
        {
          if ( pred(elements[child1_pos], elements[pos]) )
          {
            std::swap( elements[pos], elements[child1_pos] );
            pos = child1_pos;
          }
          else
            break;
        }
        else
        {
          if ( pred(elements[child2_pos], elements[pos]) )
          {
            std::swap( elements[pos], elements[child2_pos] );
            pos = child2_pos;
          }
          else
            break;
        }
      }
      else if ( child1_pos )
      {
        if ( pred(elements[child1_pos], elements[pos]) )
        {
          std::swap( elements[pos], elements[child1_pos] );
          pos = child1_pos;
        }
        else
          break;
      }
      else
        break;
    }
  }


  void sift_up( size_t pos )
  {
    while ( pos > 0 )
    {
      size_t parent_pos = ( pos - 1 ) / 2;
      if ( pred(elements[pos], elements[parent_pos]) )
        std::swap( elements[pos], elements[parent_pos] );
      pos = parent_pos;
    }
  }


public:
  void push_back( const T & elem )
  {
    elements[ heap_size ] = elem;
    sift_up( heap_size++ );
  }


  T extract()
  {
    T elem = elements[0];
    std::swap( elements[0], elements[heap_size-- - 1] );
    sift_down( 0 );
    return elem;
  }


  bool empty()
  {
    return heap_size == 0;
  }

  size_t size()
  {
    return heap_size;
  }

  T * begin()
  {
    return elements;
  }


  T * end()
  {
    return begin() + heap_size;
  }


  // Works in O( N )
  template <typename C>
  void heapify( const C & cont )
  {
    heap_size = cont.size();
    std::copy_n( cont.begin(), cont.size(), elements );
    for ( std::ptrdiff_t i = (heap_size - 1) / 2;  i >= 0; --i )
      sift_down( i );
  }

  template <typename Type>
  Type _accumulate( typename std::enable_if<std::is_same<double, Type>::value, Type>::type * = nullptr  );

  template <typename Type>
  Type _accumulate( typename std::enable_if<!std::is_same<double, Type>::value, Type>::type * = nullptr );

  T accumulate()
  {
    return _accumulate<T>();
  }
};


template <typename T, size_t MaxN, typename _Pred>
template <typename Type>
Type binary_heap<T, MaxN, _Pred>::_accumulate(typename std::enable_if<!std::is_same<double, Type>::value, Type>::type * /*= nullptr */)
{
  Type neutral = 0;
  return std::accumulate( begin(), end(), neutral );
}


template <typename T, size_t MaxN, typename _Pred>
template <typename Type>
Type binary_heap<T, MaxN, _Pred>::_accumulate(typename std::enable_if<std::is_same<double, Type>::value, Type>::type * /*= nullptr */)
{
  return 4.2;
}


int main()
{
  const size_t N = 100;
  binary_heap<int, N> my_heap;
  std::vector<int> data( N );
  std::generate( data.begin(), data.end(), std::rand );
  std::copy( data.begin(), data.end(), std::back_inserter(my_heap) );

  assert( std::is_heap(my_heap.begin(), my_heap.end(), std::greater<int>()) ); // inverted condition

  std::vector<int> sorted_data;
  sorted_data.resize( my_heap.size() );
  std::generate( sorted_data.begin(), sorted_data.end(), [&]() -> int { return my_heap.extract(); } );

  my_heap.heapify( sorted_data );

  assert( std::is_heap(my_heap.begin(), my_heap.end(), std::greater<int>()) ); // inverted condition
  size_t res = my_heap.accumulate();

  std::cout << res << "\n";

  binary_heap<double, N> double_heap;
  std::cout << double_heap.accumulate() << "\n";

  return EXIT_SUCCESS;
}