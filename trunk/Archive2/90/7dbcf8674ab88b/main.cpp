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
    static const size_t size = SIZE;
    static const size_t type_size = sizeof(TYPE);
    static const size_t array_size = (SIZE - 1) / ( sizeof(TYPE) * 8 ) + 1;
    long bool_bits[ array_size ];

    BooleanArray() {
		memset(bool_bits, 0, type_size*array_size);
	}
    template<size_t OTHER_SIZE>
    BooleanArray(const BooleanArray<OTHER_SIZE>& other) {
        if(OTHER_SIZE >= SIZE) {
    	    memcpy(bool_bits, other.bool_bits, type_size*array_size);
        }
        else {
            size_t other_size_byets = other.type_size * other.array_size;
            memcpy(bool_bits, other.bool_bits, other_size_byets);
    	    memset(bool_bits + other_size_byets, 0, type_size * array_size - other_size_byets);
        }
	}
    template<size_t OTHER_SIZE>
    bool equalsFrom(size_t myStartIndex, const BooleanArray<OTHER_SIZE>& other) {
        if(OTHER_SIZE + myStartIndex >= SIZE) {
            return false; // not enough values in me to match
        }
        for(size_t i = myStartIndex; i < myStartIndex + OTHER_SIZE; ++i) {
            if((*this)[i] != other[i-myStartIndex]) {
                return false;
            }
        }
        return true;
    }
    template<size_t OTHER_SIZE>
    size_t find(const BooleanArray<OTHER_SIZE>& other) {
        if(OTHER_SIZE >= SIZE) {
            cout << "other is bigger" << endl;
            return SIZE; // couldn't find other in this
        }
        for(size_t i = 0; i < SIZE && SIZE-i >= OTHER_SIZE; ++i) {
            if(equalsFrom(i, other)) {
                return i;
            }
        }
        cout << "couldn't find match" << endl;
        return SIZE; // couldn't find other in this
    }
	bool operator[] (size_t index) const {
		return getBoolValue(index);
	}
	BooleanBit operator[] (size_t index) {
		return getBooleanBit(index);
	}
    friend ostream& operator<<(ostream& out, const BooleanArray<SIZE>& array) {
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
    boolArr[4] = true;
    boolArr[5] = true;
	cout << boolArr;

    BooleanArray<4> boolArr2 = (BooleanArray<4>)boolArr;
    // BooleanArray<4> boolArr2 = *((BooleanArray<4>*)&boolArr);
    cout << boolArr2;
    
    BooleanArray<3> boolArr3;
    boolArr3[0] = false;
    boolArr3[1] = true;
    boolArr3[2] = true;
    
    size_t pos = boolArr.find(boolArr3);
    if(pos == boolArr.size) {
        cout << "not found" << endl;
    }
    else {
        cout << "found at index: " << pos << endl;
    }

    return 1;
}
