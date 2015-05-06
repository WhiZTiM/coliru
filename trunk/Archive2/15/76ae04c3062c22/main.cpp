#include <boost/container/static_vector.hpp>
#include <atomic>
#include <array>
#include <cstdint>
#include <iostream>


struct Batch
{
    using Offset = std::atomic<std::uint32_t>;
    
    void* allocate(std::size_t n)
    {
        auto old_offset = reinterpret_cast<std::atomic<std::uint16_t>&>(allocated_).fetch_add(n);
        auto new_offset = old_offset + n;
        if (new_offset > storage_.size())
        {
            allocated_ -= n;
            dead_ = true;
            return nullptr;
        }
        
        return &storage_[old_offset];
    }
    
    bool deallocate(void*, std::size_t n)
    {
        freed_ += n;
        assert(freed_ <= allocated_);
        if (dead_ && freed_ == allocated_)
        {
            
            
            
            
            freed_ = allocated_ = dead_ = 0;
            return true;
        }
        
        return false;
    }
    
    // 2048
    
    uint16_t allocated_;
    uint16_t freed_;
    uint8_t dead_;
    uint8_t reserved_;
    std::array<char, 2000> storage_;
};


struct BatchAllocator
{
    BatchAllocator() : mBatches(), mCurrentBatch(), mFreeList()
    {
        std::reverse(mBatches.begin(), mBatches.end());
        for (auto& batch : mBatches)
        {
            if (&batch != &mBatches.back())
            {
                mFreeList.push_back(&batch);
            }
        }
        std::cout << "mFreeList.size=" << mFreeList.size() << std::endl;
        mCurrentBatch = mFreeList.back();
        mFreeList.pop_back();
    }
    
    void* allocate(std::size_t n)
    {
        if (auto ptr = mCurrentBatch->allocate(n))
        {
            return ptr;
        }
    
        if (!mFreeList.empty())
        {
            
                auto i = (reinterpret_cast<char*>(mCurrentBatch) - reinterpret_cast<char*>(&mBatches[0])) / sizeof(Batch);
            std::cout << "Batch is dead " << i << std::endl;
            std::cout << "Selecting a new batch" << std::endl;
            mCurrentBatch = mFreeList.back();
            mFreeList.pop_back();
            auto ptr = mCurrentBatch->allocate(n);
            assert(ptr);
            return ptr;
        }
        
        throw std::bad_alloc();
    }
    
    void deallocate(void* ptr, std::size_t n)
    {
        std::cout << "deallocate " << n << " bytes" << std::endl;
        auto i = (static_cast<char*>(ptr) - reinterpret_cast<char*>(&mBatches[0])) / sizeof(Batch);
        auto& batch = mBatches[i];
        if (batch.deallocate(ptr, n))
        {
            
                auto i = (reinterpret_cast<char*>(&batch) - reinterpret_cast<char*>(&mBatches[0])) / sizeof(Batch);
                std::cout << "Reviving a dead batch " << i << std::endl;
        
        
            batch = Batch();
            mFreeList.push_back(&batch);
        }
    }
    
    std::array<Batch, 20> mBatches;
    Batch* mCurrentBatch;
    boost::container::static_vector<Batch*, 20> mFreeList;
};


int main()
{
    BatchAllocator alloc;
    
    
    std::vector<std::pair<void*, std::size_t>> vec;
    for (int i = 0; i != 500; i++)
    {
        std::cout << '\n' << i << ": ";
        
        vec.push_back(std::pair<void*, std::size_t>(alloc.allocate(i), i));
        
        if (i >= 0 && rand() % 10 == 0)
        {
            for (auto pair : vec)
            {
                alloc.deallocate(pair.first, pair.second);
                vec.clear();
            }
        }
    }
    std::cout << "\n\n*** Performing cleanup ***" << std::endl;
            for (auto pair : vec)
            {
                alloc.deallocate(pair.first, pair.second);
                vec.clear();
            }
    
    std::cout << "End of program" << std::endl;
}