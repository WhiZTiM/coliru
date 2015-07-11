#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/filesystem/path.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
namespace io = boost::iostreams;
namespace fs = boost::filesystem;

class FastaReader {

public:
    typedef std::pair<boost::string_ref, boost::string_ref> Entry;
    typedef std::vector<Entry> Data;

private:
    Data fV;
    fs::path file;  

public:
    FastaReader(const fs::path & f);
    ~FastaReader();

    const fs::path & getFile() const;
    const Data::const_iterator begin() const;
    const Data::const_iterator end() const;   

private:
    io::mapped_file_source mmap;
    void parse();
};

#include <iomanip>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
//#include "fastaReader.hpp"

#include <boost/iostreams/device/mapped_file.hpp>

using namespace std;

namespace fs = boost::filesystem;
namespace qi = boost::spirit::qi;
namespace pt = boost::posix_time;
namespace io = boost::iostreams;

namespace boost { namespace spirit { namespace traits {
    template <typename It>
    struct assign_to_attribute_from_iterators<boost::string_ref, It, void> {
        static void call(It f, It l, boost::string_ref& attr) { attr = boost::string_ref { f.base(), size_t(std::distance(f.base(),l.base())) }; }
    };
} } }

template <typename Iterator>
struct FastaGrammar : qi::grammar<Iterator, FastaReader::Data()> {

    FastaGrammar() : FastaGrammar::base_type(fasta) {
        using namespace qi;
        using boost::phoenix::construct;
        using boost::phoenix::begin;
        using boost::phoenix::size;

        entry = ('>' >> raw[ *~char_('\n') ] >> '\n' >> raw[ *~char_('>') ]);
        fasta = *entry >> *eol >> eoi ;

        BOOST_SPIRIT_DEBUG_NODES((fasta)(entry));
    }
  private:
    qi::rule<Iterator, FastaReader::Data()>  fasta;
    qi::rule<Iterator, FastaReader::Entry()> entry;
};

FastaReader::FastaReader(const fs::path & f) : file(f), mmap(file.c_str()) {
    parse();
}

FastaReader::~FastaReader() {}

const fs::path & FastaReader::getFile() const {
    return this->file;
}


const FastaReader::Data::const_iterator FastaReader::begin() const {
    return this->fV.cbegin();
}


const FastaReader::Data::const_iterator FastaReader::end() const {
    return this->fV.cend();
}

void FastaReader::parse() {
    if (this->file.empty())                throw std::runtime_error("FastaReader: No file specified.");
    if (! fs::is_regular_file(this->file)) throw std::runtime_error(string("FastaReader: File not found: ") + this->file.string());

    typedef char const*                                     iterator_type;
    typedef boost::spirit::line_pos_iterator<iterator_type> pos_iterator_type;
    typedef FastaGrammar<pos_iterator_type>                 fastaGr;

    static const fastaGr fG{};
    try {
        std::cerr << "Measuring: Parsing." << std::endl;
        const pt::ptime startMeasurement = pt::microsec_clock::universal_time();

        pos_iterator_type first(mmap.data()), last(mmap.end());
        qi::parse<pos_iterator_type>(first, last, fG, this->fV);

        const pt::ptime endMeasurement = pt::microsec_clock::universal_time();
        pt::time_duration duration (endMeasurement - startMeasurement);
        std::cerr << duration <<  std::endl;
    } catch (std::exception const& e) {
        cerr << "error message: " << e.what() << endl;
    }   
}

int main() {
    FastaReader reader("input.txt");

    //for (auto& e : reader) std::cout << '>' << e.first << '\n' << e.second << "\n\n";
}
