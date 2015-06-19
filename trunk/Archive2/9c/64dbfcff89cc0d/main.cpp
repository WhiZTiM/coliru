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

template<size_t SIZE, typename INTERNAL = long long> // size_t = unsigned int, SIZE represents number of booleans to store
class BooleanArray
{
    // bool_bits hold boolean values in bits
	// the required size for this array = SIZE divided by number of bits
	static const size_t array_size = (SIZE - 1) / ( sizeof(INTERNAL) * 8 ) + 1;
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
	BooleanArray() {
		cout << "SIZE = " << SIZE << ", sizeof(INTERNAL) = " << sizeof(INTERNAL) << ", array_size = " << array_size << ", physical size = " << array_size * sizeof(INTERNAL) * 8 << endl;
		// init the array to all false
		memset(bool_bits, 0, sizeof(INTERNAL) * array_size);
	}
	bool operator[] (size_t index) const {
		return getBoolValue(index);
	}
	BooleanBit operator[] (size_t index) {
		cout << index << endl;
		return getBooleanBit(index);
	}
};

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
	BooleanArray<size> boolArr;
	// bool boolArr[size] = { 0 };

	boolArr[0] = true;
	boolArr[63] = true;
	boolArr[64] = true;
	boolArr[65] = true;
	boolArr[size-1] = true;
	boolArr[125] = true; // outside the array but in the physical size
	boolArr[127] = true; // outside the array but in the physical size
	// boolArr[128] = true;

	print(boolArr);

    boolArr[63] = false;
	boolArr[7] = false;
	boolArr[12] = true;
	boolArr[110] = true;
	boolArr[119] = false;

	print(boolArr);

	return 1;
}
