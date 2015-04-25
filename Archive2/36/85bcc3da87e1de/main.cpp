#include <iostream>
#include <fstream> 
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace Media {
    struct Author {
        std::string name;
        Author(std::string name = "") : name(std::move(name)) {}
    };

    using AuthorRef = boost::shared_ptr<Author>;

    struct CommonInfo {
        std::string name;
        int         year;
        AuthorRef   author;
    };

    struct BookInfo : CommonInfo {
        BookInfo() = default;

        int pageNum;
        int print;
        int value;

        BookInfo(CommonInfo ci, int pageNum, int print, int value) :
            CommonInfo(ci), pageNum(pageNum), print(print), value(value)
        { }
    };

    struct VideoInfo : CommonInfo {
        VideoInfo(CommonInfo ci = {}) : CommonInfo(ci) { }
    };

    struct MusicInfo : CommonInfo {
        MusicInfo(CommonInfo ci = {}) : CommonInfo(ci) { }
    };

    using Object  = boost::variant<BookInfo, MusicInfo, VideoInfo>;
    using Catalog = std::vector<Object>;

    ////// serialization methods
    static inline std::ostream& operator<<(std::ostream& os, CommonInfo const& ci) { return os << ci.name << " (" << ci.author->name << ")"; }

    // out-of-class serialization
    template <typename Ar> void serialize(Ar& ar, VideoInfo& o, unsigned) { ar & boost::serialization::base_object<CommonInfo>(o); }
    template <typename Ar> void serialize(Ar& ar, MusicInfo& o, unsigned) { ar & boost::serialization::base_object<CommonInfo>(o); }
    template <typename Ar> void serialize(Ar& ar, CommonInfo&o, unsigned) {
        ar & o.name & o.year & o.author;
    }
    template <typename Ar> void serialize(Ar& ar, Author& o,    unsigned) {
        ar & o.name;
    }
    template <typename Ar> void serialize(Ar& ar, BookInfo& o,  unsigned) {
        ar  & boost::serialization::base_object<CommonInfo>(o)
            & o.pageNum 
            & o.print
            & o.value
            ;
    }
}

struct Library {
    std::vector<Media::AuthorRef> authors; // to allow unreferenced authors
    Media::Catalog catalog;

    static Library makeSample();

    static Library load(std::string const& fname);
    void save(std::string const& fname) const;

    template <typename Ar> void serialize(Ar&ar,unsigned) {
        ar & authors & catalog;
    }
};

////////////////////////////////////////////////////////
// Main
int main() {
    Library::makeSample().save("authorsAndItems.dat");

    auto cloned = Library::load("authorsAndItems.dat");

    for (auto& obj : cloned.catalog)
        std::cout << obj << "\n";
}

using namespace Media;

Library Library::makeSample() {
    using boost::make_shared;
    // shared author
    auto multaScripserat = make_shared<Author>("Scripserat, Multa T.");

    return {
        {
            multaScripserat,
            boost::make_shared<Author>(Author{"Sufferer, A."}), // no books/music survived
        },
        {
            BookInfo { CommonInfo { "Title 1", 1999, multaScripserat }, 453, 7, 3 },
            BookInfo { CommonInfo { "Title 2", 2011, multaScripserat }, 200, 5, 1 },
            MusicInfo { { "Pop Album", 1972, make_shared<Author>("Beatles, The") } },
            MusicInfo { { "Title 2", 2011, multaScripserat } },
            VideoInfo { { "The Battleship Potemkin", 1925, make_shared<Author>("Eisenstein, Sergei") } },
        }
    };
}

void Library::save(std::string const& fname) const {
    std::ofstream ofs(fname, std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);

    oa << *this;
}

Library Library::load(std::string const& fname) {
    std::ifstream ifs(fname, std::ios::binary);
    boost::archive::binary_iarchive ia(ifs);

    Library lib;
    ia >> lib;

    return lib;
}

