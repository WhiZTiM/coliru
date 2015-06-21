//---------------------------------------
// example of:
// - bit array for booleans
// - proxy class for returned val
// inspired by the STL implementation
// and Scott Meyers Modern C++ item 6.
//---------------------------------------
// Amir Kirsh, amirk@mta.ac.il
//---------------------------------------
#include <cstring> // for memset
#include <iostream>
#include <cmath>

using namespace std;

template<size_t SIZE>
class BooleanArray
{
    // bool_bits hold boolean values in bits
	// the required size for this array = SIZE divided by number of bits
    typedef long TYPE; // the internal type
    static const TYPE _1 = 1;
    static const size_t type_size = sizeof(TYPE);    
	static const size_t array_size = (SIZE - 1) / ( sizeof(TYPE) * 8 ) + 1;
	long bool_bits[ array_size ];
	class BooleanBit
	{
		TYPE* bool_bits; // the entire array
		size_t byte_index;  // the byte index in the array where the bit is located
		char bit_index; // a number between 0-7 pointing to the actual bit
	public:
		BooleanBit(TYPE* _bool_bits, size_t _byte_index, char _bit_index) 
			: bool_bits(_bool_bits), byte_index(_byte_index), bit_index(_bit_index) {}
		operator bool()const {
			return (bool_bits[byte_index] & (_1 << bit_index)) != 0; // return the bit at the bit index, in *byte
		}
		bool operator=(bool val) {
            if(val != (bool)*this) {
    			cout << "a change on: byte_index = " << byte_index << " and bit_index = " << (int)bit_index << endl;
    			if(val) {
    				bool_bits[byte_index] |= ( _1 << bit_index ); // setting a bit to true 
    			} else {
    				bool_bits[byte_index] &= ~( _1 << bit_index ); // setting a bit to false 
    			}
            }
			return val;
		}
	};
	bool getBoolValue(size_t index)const {
		return (bool) ( const_cast<BooleanArray*>(this)->getBooleanBit(index) );
	}
	BooleanBit getBooleanBit(size_t i) {
		return BooleanBit(bool_bits, i/(type_size*8), i%(type_size*8));
	}
public:
	BooleanArray() {
		memset(bool_bits, 0, type_size*array_size);
	}
	bool operator[] (size_t index) const {
		return getBoolValue(index);
	}
	BooleanBit operator[] (size_t index) {
		return getBooleanBit(index);
	}
};

template<size_t PARAM_ARRAY_SIZE>
BooleanArray<PARAM_ARRAY_SIZE> createBooleanArray(bool (&boolean_array)[PARAM_ARRAY_SIZE]) {
    BooleanArray<PARAM_ARRAY_SIZE> new_array;
    for(size_t i=0; i<PARAM_ARRAY_SIZE; ++i) {
        if(boolean_array[i]) {
            new_array[i] = true;
        }
    }
    return new_array;
}

template<size_t SIZE>
void print(const BooleanArray<SIZE>& array) {
	for(size_t i=0; i<SIZE; ++i) {
		if(array[i]) {
			cout << i << endl;
		}
	}
}

int main() {
	
	const size_t size = 120;
//	BooleanArray<size> boolArr;
	bool boolArr[size] = { 0 };

	boolArr[0] = true;
	boolArr[63] = true;
	boolArr[64] = true;
	boolArr[65] = true;
	boolArr[size-1] = true;
	boolArr[125] = true; // outside the array but in the physical size
	boolArr[127] = true; // outside the array but in the physical size
	// boolArr[128] = true;

	print(createBooleanArray(boolArr));

    boolArr[63] = false;
	boolArr[7] = false;
	boolArr[12] = true;
	boolArr[110] = true;
	boolArr[119] = false;

    print(createBooleanArray(boolArr));

	return 1;
}
