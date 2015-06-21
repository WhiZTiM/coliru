//---------------------------------------
// example of:
// - bit array for booleans
// - proxy class for returned val
// inspired by the STL implementation
// and Scott Meyers Modern C++ item 6.
//---------------------------------------
// Amir Kirsh, amirk@mta.ac.il
//---------------------------------------
// This version can be found at:
// <this link>
// I created different versions of this example, see:
// http://coliru.stacked-crooked.com/a/0b501b1700ff6bd5 - without the inheritance, but with the create from bool[]
// http://coliru.stacked-crooked.com/a/907dbcf8674ab88b - without the inheritance, but with find between different size arrays and operator<<
// http://coliru.stacked-crooked.com/a/2ab128049fd39212
// http://coliru.stacked-crooked.com/a/27d45f004cdad73b
// can also run on: http://www.tutorialspoint.com/compile_cpp11_online.php

#include <cstring> // for memset
#include <iostream>
#include <cmath>

using namespace std;

class AllSizeBooleanArray {
    void* bool_bits_arr_ptr;
protected:
    AllSizeBooleanArray(void* _bool_bits_arr_ptr): bool_bits_arr_ptr(_bool_bits_arr_ptr) {}
	constexpr static size_t array_size(size_t SIZE, size_t unit_size) {
		return (SIZE - 1) / (unit_size * 8) + 1;
	}
public:
	void cloneToOther(AllSizeBooleanArray* other, size_t physical_size)const {
		memcpy(other->bool_bits_arr_ptr, bool_bits_arr_ptr, physical_size);
	}
};

template<size_t SIZE, typename INTERNAL = int> // size_t = unsigned int, SIZE represents number of booleans to store
class BooleanArray: public AllSizeBooleanArray
{
	// bool_bits hold boolean values in bits
	// the required size for this array = SIZE divided by number of bits
	static const size_t array_size = AllSizeBooleanArray::array_size(SIZE, sizeof(INTERNAL));
    INTERNAL bool_bits[ array_size ];
	class BooleanBit
	{
		INTERNAL* bool_bits; // the entire array
		size_t byte_index;  // the byte index in the array where the bit is located
		char bit_index; // a number between 0-7 pointing to the actual bit
	public:
		BooleanBit(INTERNAL* _bool_bits, size_t _byte_index, char _bit_index) 
			: bool_bits(_bool_bits), byte_index(_byte_index), bit_index(_bit_index) {}
		operator bool()const {
			INTERNAL _1 = 1;
			return (bool_bits[byte_index] & (_1 << bit_index)) != 0; // return the bit at the bit index, in *byte
		}
		bool operator=(bool val) {
			cout << "a change on: byte_index = " << byte_index << " and bit_index = " << (int)bit_index << endl;
			INTERNAL _1 = 1;
			if(val) {
				bool_bits[byte_index] |= ( _1 << bit_index ); // setting a bit to true 
			} else {
				bool_bits[byte_index] &= ~( _1 << bit_index ); // setting a bit to false 
			}
			return val;
		}
	};
	bool getBoolValue(size_t index)const {
		// we know that getBooleanBit doesn't change anything,
		// it's not declared const since it 'allows' to change based on its return value
		// but we know that we take the return value and turn it into a simple bool byval
		// so we are not worried about the below constness casting
		return (bool) ( const_cast<BooleanArray*>(this)->getBooleanBit(index) );
	}
	BooleanBit getBooleanBit(size_t index) {
		size_t byte_index = index / (sizeof(INTERNAL) * 8);  // index of the byte in the bool_bits array
		char bit_index = index % (sizeof(INTERNAL) * 8);  // index of the bit in this byte
		return BooleanBit(bool_bits, byte_index, bit_index);
	}
public:
    static const size_t actual_physical_size = array_size * sizeof(INTERNAL);
    static const size_t size = SIZE;
	BooleanArray(): AllSizeBooleanArray(bool_bits) {
		cout << "SIZE = " << SIZE << ", array_size = " << array_size << ", sizeof(INTERNAL) = " << sizeof(INTERNAL) << ", actual_physical_size = " << actual_physical_size << endl;
		// init the array to all false
		memset(bool_bits, 0, actual_physical_size);
	}
    
    template<size_t OTHER_SIZE>
	BooleanArray(const BooleanArray<OTHER_SIZE>& other): AllSizeBooleanArray(bool_bits) {
		size_t size_to_clone = BooleanArray<OTHER_SIZE>::actual_physical_size < actual_physical_size ? BooleanArray<OTHER_SIZE>::actual_physical_size : actual_physical_size; 
        cout << "in c'tor from other, OTHER_SIZE = " << OTHER_SIZE << ", my SIZE = " << SIZE << ", physical size_to_clone in bits = " << size_to_clone * 8 << endl;
		other.cloneToOther(this, size_to_clone);
		if(OTHER_SIZE < SIZE) {
            memset(bool_bits + size_to_clone, 0, actual_physical_size - size_to_clone);
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
		cout << index << endl;
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

// create a BooleanArray fron bool[] array, without a need to get size parameter!
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
    cout << "in print SIZE: " << SIZE << endl;
	for(size_t i=0; i<SIZE; ++i) {
		if(array[i]) {
			cout << i << endl;
		}
	}
}

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

    bool squareBracketsBooleanArray[] = {true, false, true};
    auto boolArr4 = createBooleanArray(squareBracketsBooleanArray);  
    cout << boolArr4;

    return 1;
}
