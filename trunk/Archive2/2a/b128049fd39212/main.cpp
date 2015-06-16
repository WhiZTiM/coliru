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
	void cloneToOther(AllSizeBooleanArray* other, size_t phisical_size)const {
		memcpy(other->bool_bits_arr_ptr, bool_bits_arr_ptr, phisical_size);
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
	BooleanArray(): AllSizeBooleanArray(bool_bits) {
		cout << "SIZE = " << SIZE << ", array_size = " << array_size << ", sizeof(INTERNAL) = " << sizeof(INTERNAL) << endl;
		// init the array to all false
		memset(bool_bits, 0, sizeof(INTERNAL) * array_size);
	}
	template<size_t OTHER_SIZE>
	BooleanArray(const BooleanArray<OTHER_SIZE>& other): AllSizeBooleanArray(bool_bits) {
    	memset(bool_bits, 0, sizeof(INTERNAL) * array_size);
		size_t size_to_clone = BooleanArray<OTHER_SIZE>::actual_physical_size < actual_physical_size ? BooleanArray<OTHER_SIZE>::actual_physical_size : actual_physical_size; 
        cout << "in c'tor from other, OTHER_SIZE = " << OTHER_SIZE << ", my SIZE = " << SIZE << ", physical size_to_clone in bits = " << size_to_clone * 8 << endl;
		other.cloneToOther(this, size_to_clone);
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
    cout << "in print SIZE: " << SIZE << endl;
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

	boolArr[1] = true;
    boolArr[6] = true;
    boolArr[7] = true;
    boolArr[8] = true;
    boolArr[25] = true;
	boolArr[63] = true;
	boolArr[64] = true;
	boolArr[65] = true;
	boolArr[size-1] = true;
	boolArr[125] = true;
	boolArr[127] = true;
	// boolArr[128] = true;

    cout << "print: " << endl;
    print(boolArr);
    cout << "print<130>: " << endl;
	print<130>(boolArr);

    print<10>(boolArr);


	/*
	for(int i=0; i<130; ++i) {
		if(boolArr[i]) {
			cout << i << endl;
		}
	}
	*/


	/*
	boolArr[7] = false;
	boolArr[12] = true;
	boolArr[size-2] = true;
	boolArr[size-1] = false;

	print(boolArr);
	*/

	return 1;
}
