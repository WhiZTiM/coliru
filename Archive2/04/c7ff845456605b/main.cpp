
// ArbitraryCaching

class CachedListing
{
    LanguageListing listing;
    system::steady_clock::timepoint expires_at;
}

/**
 * @brief Wrapper around an immutable, cached object.
 * 
 * Uses CRTP (look it up)
 * 
 * The cached object being const makes it thread safe.
 * 
 * There's definitely a chance that the underlying data can be double updated pretty quickly, but
 * for the intended use cases I have it's a non-issue (think reading out mostly static data such as
 * language listings / listings of licence codes and keeping them for a hour.)
 * 
 * it's not too hard to convert to force only a single update, it means taking the unique_lock,
 * checking HasExpired again, Regenerating and then releasing the lock.
 * 
 * Users calling Get() need to deal with any possible exceptions from Regenerate
 * 
 * 
 * Cloud possible remove the CachedType template param and move it to a typedef on DerivedType, I
 * feel this is more obvious though.
 */
template<typename CachedType, typename DerivedType>
class CachedObject
{
    std::shared_ptr<const CachedType> Get()
    {
        std::shared_ptr<const CachedType> item;
        {
            shared_lock_guard(lock);
            item = storage;
        }
        
        if (!item || static_cast<DerivedType*>(this)->HasExpired(*item))
        {
            item = static_cast<DerivedType*>(this)->Regenerate();
            {
                unique_lock_guard(lock);
                storage = item;
            }
            return item;
        }
        return item;
    }
    
private:
    mutable std::shared_lock lock;
    std::shared_ptr<const CachedType> storage;
};

class CachedLanguageListing : CachedObject<CachedListing, CachedLanguageListing>
{
    std::shared_ptr<const CachedType> Regenerate()
    {
        std::shared_ptr<CachedType> result = make_shared<CachedListing>();
        result.listing = query_from_database();
        result.expires_at = now + std::chrono::hour{1};
        return result;
    }
    
    bool HasExpired(const CachedType& item) const
    {
        return item.expires_at > std::chrono::steady_clock::now();
    }
}
