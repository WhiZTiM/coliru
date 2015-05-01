#include <iostream>
#include <algorithm>
#include <vector>

class MemoryBlock
{
public:

    // 생성자
    MemoryBlock(size_t length) : _length(length) , _data(new int[length]){}
    // 소멸자
    ~MemoryBlock()
    {
        if (_data != NULL)
        {
            delete[] _data;  // 리소스 삭제
        }
    }
    // 복사 생성자
    MemoryBlock(const MemoryBlock& copy): _length(copy._length) , _data(new int[copy._length]){}

    // 대입 연산자
    MemoryBlock& operator=(const MemoryBlock& other)
    {
        if (this != &other)
        {
            delete[] _data;  // 기존 리소스 삭제

            _length = other._length;
            _data = new int[_length];
            std::copy(other._data, other._data + _length, _data);
        }
        return *this;
    }

    // 리소스의 길이를 반환
    size_t Length() const
    {
        return _length;
    }

private:
    size_t _length;  // 리소스 길이
    int* _data;      // 리소스
};

int main()
{
    std::vector<MemoryBlock> v;
    v.push_back(MemoryBlock(25));
    v.push_back(MemoryBlock(75));

    // 첫 번째 원소를 다른 MemoryBlock 으로 변경
    v[0] = MemoryBlock(50);
}