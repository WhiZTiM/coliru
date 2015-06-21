#include <cstring> // for memset
#include <iostream>
using namespace std; template<size_t SIZE> class BooleanArray { // same line numbers as in the exam
  typedef char TYPE; // our internal type is char, which is 1 byte
  static const size_t type_size_bytes = sizeof(TYPE);
  static const size_t type_size_bits = type_size_bytes * 8;
  static const size_t array_size = (SIZE - 1) / type_size_bits + 1;
  TYPE bool_bits[ array_size ];
  static const TYPE _1 = 1;
  // inner class
  class BooleanBit {
    TYPE* bool_bits;   // the entire array
    size_t type_index; // the index in the array where bit sits
    char bit_index;    // a number between 0 and type_size_bits-1
    size_t index()const {
      return type_index * type_size_bits + bit_index;
    }
  public:
    BooleanBit(TYPE* bits, size_t t_index, char b_index)
    : bool_bits(bits), type_index(t_index), bit_index(b_index) {}
    operator bool()const {
      // return the relevant bit value
      return bool_bits[type_index] & (_1 << bit_index);
    }
    bool operator=(bool val) {
      if(val != (bool)*this) {
        cout << "changing index " << index()
             << " to " << (val?"true":"false") << endl;
        if(val) {
          // setting a bit to true
          bool_bits[type_index] |= ( _1 << bit_index ); 
        } else {
          // setting a bit to false
          bool_bits[type_index] &= ~( _1 << bit_index );  
        }
      }
      return val;
    }
  }; // end of inner class BooleanBit

  bool getBoolValue(size_t index)const {
    return (bool)
       ( const_cast<BooleanArray*>(this)->getBooleanBit(index) );
  }
  BooleanBit getBooleanBit(size_t i) {
    return BooleanBit
       (bool_bits, i/(type_size_bits), i%(type_size_bits));
  }
public:
  static const size_t size = SIZE;
  BooleanArray() {
    memset(bool_bits, 0, type_size_bytes * array_size);
  }
  template<size_t OTHER_SIZE>
  bool equalsFrom(size_t from, const BooleanArray<OTHER_SIZE>& o){
    if(OTHER_SIZE + from > SIZE) {
      return false; // not enough values in me to match
    }
    for(size_t i=from; i < from + OTHER_SIZE; ++i) {
      if((*this)[i] != o[i-from]) {
        return false;
      }
    }
    return true;
  }
  template<size_t OTHER_SIZE>
  size_t find(const BooleanArray<OTHER_SIZE>& o) {
    if(OTHER_SIZE > SIZE) {
      cout << "other is bigger" << endl;
      return SIZE; // couldn't find other in this
    }
    for(size_t i = 0; i < SIZE && SIZE-i >= OTHER_SIZE; ++i) {
      if(equalsFrom(i, o)) {
        return i;
      }
    }
    return SIZE; // couldn't find other in this
  }
  bool operator[] (size_t index) const { // cout << "const []" << endl;
    return getBoolValue(index);
	 }
	 BooleanBit operator[] (size_t index) {
    return getBooleanBit(index);
	 }
  friend ostream& operator<<
  (ostream& out, const BooleanArray<SIZE>& array) {
    for(size_t i=0; i<SIZE; ++i) {
      if(array[i]) {
        out << i << endl;
      }
    }
    return out;
  }
};

int main() {
  BooleanArray<10> boolArr;
  boolArr[0] = true;
  boolArr[1] = false;
  boolArr[2] = false;
  boolArr[3] = true;
  BooleanArray<3> boolArr2;
  boolArr2[0] = false;
  boolArr2[1] = true;
  boolArr2[2] = false;
  size_t pos = boolArr.find(boolArr2);
  if(pos == boolArr.size) {
    cout << "not found" << endl;
  }
  else {
    cout << "found at index: " << pos << endl;
  }
  return 1;
}