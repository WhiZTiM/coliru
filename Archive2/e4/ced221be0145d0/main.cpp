#include <algorithm>
#include <cstdint>
#include <cstring>


// Contains information about the processor. 
// Describes Snapshot and Config types, but
// lets the user decide on where to store those
// objects.
struct SizeCounterTraits
{
    // Properties that can be queried at compile-time.
    // Since we only need the size of the packet the 
    // parent processor can keep a queue of sizes and
    // and let the packet go out of scope even before
    // the size is processed.
    enum 
    {
        needs_size = true,
        needs_payload = false,
        needs_timestamp = false
    };
    
    // Config and Snapshot are stored *outside* of this class
    // and are passed as parameters initialize() and update() calls.
    //
    // Delegating the storage to the higher layer code allows us
    // the flexibility in designing a cache-friendly data layout.
    struct Snapshot
    {   
         // Initializes the snapshot state with the first frame.
         // The first frame is often a special case.
         // By handling it separately we can simplify the logic
         // (and eliminate branches) in the normal update call.
        void initialize(std::int32_t size)
        {   
            mMinimum = size;
            mMaximum = size;
            mBytes = size;
            mFrames = 1;
        }
        
        // The normal update call
        void update(std::int32_t size)
        {
            mMinimum = std::min(mMinimum, size);
            mMaximum = std::max(mMaximum, size);
            mBytes += size;
            mFrames++;
        }
        
        // Take care to not introduce any padding here.
        std::int32_t mMinimum;
        std::int32_t mMaximum;
        std::int64_t mBytes;
        std::int64_t mFrames;
    };
    
    struct Config {};
};


struct LatencyCounterTraits
{
    enum 
    {
        needs_size = false,
        needs_payload = true, // because we must extract the time tag
        needs_timestamp = true
    };
    
    struct Snapshot
    {   
        void initialize(std::int64_t latency)
        {
            mMinimum = latency;
            mMaximum = latency;
            mTotal = latency;
            mCounter = 1;
        }
        
        void update(std::int64_t latency)
        {
            mMinimum = std::min(mMinimum, latency);
            mMaximum = std::min(mMaximum, latency);
            mTotal += latency;
            mCounter++;
        }
        
        double average() const
        {
            return 1.0 * mTotal / mCounter;;
        }
        
        std::int64_t mMinimum;
        std::int64_t mMaximum;
        std::int64_t mTotal;
        std::int64_t mCounter;
    };
    
    struct Config
    {
        void setTagOffset(std::int32_t offset)
        {
            mOffset = offset;
        }
        
        std::int64_t getEmbeddedTimestamp(const std::uint8_t* frame_data, std::int32_t frame_length) const
        {
            std::int64_t result;
            std::memcpy(&result, frame_data + (frame_length - mOffset), sizeof(result));
            return result;
        }
        
        std::int32_t mOffset = 0;
    };
};


