#include <iosfwd>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/iostreams/stream.hpp>

class SourceBuffer {
  private:
    FILE *file;

  public:
    typedef char                                   char_type;
    typedef boost::iostreams::seekable_device_tag  category;

#if 1
    std::streamsize read(char*, std::streamsize n) 
        {
            // Read up to n characters from the input 
            // sequence into the buffer s, returning   
            // the number of characters read, or -1 
            // to indicate end-of-sequence.
            return n;
        }
    std::streamsize write(const char*, std::streamsize n) 
        {
            // Write up to n characters from the buffer
            // s to the output sequence, returning the 
            // number of characters written
            return n;
        }
    std::streampos seek(boost::iostreams::stream_offset off, std::ios_base::seekdir) 
        {
            // Advances the read/write head by off characters, 
            // returning the new position, where the offset is 
            // calculated from:
            //  - the start of the sequence if way == ios_base::beg
            //  - the current position if way == ios_base::cur
            //  - the end of the sequence if way == ios_base::end
            return off;
        }
#else
    typedef char char_type;
    typedef boost::iostreams::input_seekable category;

    std::streamsize read(char * /*s*/, std::streamsize n) {
        return n;
    }

    boost::iostreams::stream_offset seek(boost::iostreams::stream_offset /*off*/, std::ios_base::seekdir /*way*/) {
        return 0;
    }
#endif
    SourceBuffer(const char * /*fileName*/ = "") {}
    ~SourceBuffer() {}

    void open(const char * /*fileName*/) {}
    void close() {}
};

int main(void)
{
    boost::iostreams::stream<SourceBuffer> example("test.txt");
}
