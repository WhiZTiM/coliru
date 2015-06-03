#include <cstdio>
#include <string>
#include <vector>

/*
*   FileInfo as abstract interface example
*/
class FileInfo
{
public:
	virtual const char* STORAGE_METHOD_CALL url() const = 0;

	virtual uint64_t STORAGE_METHOD_CALL size() const = 0;

	virtual int STORAGE_METHOD_CALL type() const = 0;
    
    public:
		virtual void STORAGE_METHOD_CALL release() = 0;
};

class FileInfoIterator
{
public:
	virtual void STORAGE_METHOD_CALL reset() = 0;

	virtual FileInfo* STORAGE_METHOD_CALL get() const = 0;

	virtual void STORAGE_METHOD_CALL next() const = 0;

	virtual int STORAGE_METHOD_CALL eos() const = 0;

public:
	virtual void STORAGE_METHOD_CALL release() = 0;
};

void workWithFileInfoClass(FileInfoIterator* fit)
{
    FileInfo* fi = fit->get();
    std::printf(
        "File url: %s, size: %u, type: %u\n", 
        fi->url(),
        fi->size(),
        fi->type()
    );
    fi->release()    
}


/*
*   FileInfo as struct example
*/
struct FileInfo2
{
    char*       url;
    uint64_t    size;
    int         type;
};

class FileInfoIterator
{
public:
    virtual void STORAGE_METHOD_CALL reset() = 0;

    // return size of 'url' to be allocated by user
	virtual uint32_t STORAGE_METHOD_CALL get(FileInfo* fi) const = 0;

	virtual void STORAGE_METHOD_CALL next() const = 0;

	virtual int STORAGE_METHOD_CALL eos() const = 0;

public:
	virtual void STORAGE_METHOD_CALL release() = 0;
};

void workWithFileInfoClass(FileInfoIterator* fit)
{
    FileInfo fi;
    uint32_t url_size = fit->get(nullptr);
    
    fi.url = static_cast<char*>(malloc(url_size));
    fit->get(&fi);
    
    std::printf(
        "File url: %s, size: %u, type: %u\n", 
        fi.url,
        fi.size,
        fi.type
    );
    free(fi.url);    
}



int main()
{
}
