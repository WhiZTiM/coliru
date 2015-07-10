#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;


class FastaReader {

public:
    typedef std::pair<std::string, std::string> Entry;
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
    void parse();

};

#include <iomanip>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
//#include "fastaReader.hpp"

#include <boost/iostreams/device/mapped_file.hpp>

using namespace std;

namespace fs = boost::filesystem;
namespace qi = boost::spirit::qi;
namespace pt = boost::posix_time;
namespace io = boost::iostreams;

template <typename Iterator>
struct FastaGrammar : qi::grammar<Iterator, FastaReader::Data()> {
    qi::rule<Iterator, FastaReader::Data()> fasta;

    FastaGrammar() : FastaGrammar::base_type(fasta) {
        using namespace qi;

        fasta = *('>' >> *~char_('\n') >> '\n' 
                      >> *~char_('>')) 
                >> *eol
                >> eoi
                ;

        BOOST_SPIRIT_DEBUG_NODES((fasta));
    }
};


FastaReader::FastaReader(const fs::path & f) : file(f) {
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

    typedef char const*                                               iterator_type;
    typedef boost::spirit::classic::position_iterator2<iterator_type> pos_iterator_type;
    typedef FastaGrammar<pos_iterator_type>                           fastaGr;

    io::mapped_file_source mmap(file.c_str());

    static const fastaGr fG{};
    try {
        std::cerr << "Measuring: Parsing." << std::endl;
        const pt::ptime startMeasurement = pt::microsec_clock::universal_time();

        pos_iterator_type first(iterator_type{mmap.data()}, iterator_type{mmap.end()}, file.string());
        qi::phrase_parse<pos_iterator_type>(first, {}, fG, boost::spirit::ascii::space, this->fV);

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
