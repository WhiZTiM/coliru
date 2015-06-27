#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <map>
#include <iomanip> // setw, for debug output
#include <cassert>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
// #include <eigen3/Eigen/Core>
// #include <eigen3/Eigen/Dense>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace ast {
    struct column_definition {
        int index;
        std::string alpha_id;
        std::string type, function;
        bool mapped;
        std::string name;
    };

    namespace bmi = boost::multi_index;

    using column_definitions = boost::multi_index_container<
            column_definition, 
            bmi::indexed_by<
                bmi::random_access<bmi::tag<struct by_default> >,
                bmi::ordered_unique<bmi::tag<struct by_idx>, bmi::member<column_definition, int, &column_definition::index> >
            >
        >;

    struct column_mapping {
        using table  = std::map<int, std::string>;
        std::string alpha_id;
        table mappings;
        
        struct record {
            int value;
            std::string text;

            operator std::pair<table::key_type, table::mapped_type>() const { 
                return { value, text }; 
            }
        };
    };

    using column_mappings = std::vector<column_mapping>;

    struct metadata {
        column_definitions coldefs;
        column_mappings colmaps;
    };

    using cell = int; // or double? CAUTION: double doesn't work well as a key in a map

    struct data {
        using cells = std::vector<std::vector<cell> >;
        cells _cells;
    };

    struct contents {
        metadata _meta;
        data     _data;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::column_definition,
        (int, index)
        (std::string, alpha_id)
        (std::string, type)
        (std::string, function)
        (bool, mapped)
        (std::string, name))

BOOST_FUSION_ADAPT_STRUCT(ast::metadata,
        (ast::column_definitions, coldefs)
        (ast::column_mappings, colmaps)
        )

BOOST_FUSION_ADAPT_STRUCT(ast::column_mapping,
        (std::string, alpha_id)
        (ast::column_mapping::table, mappings)
        )

BOOST_FUSION_ADAPT_STRUCT(ast::column_mapping::record,
        (std::string, text)
        (int, value)
        )

BOOST_FUSION_ADAPT_STRUCT(ast::data,
        (ast::data::cells, _cells)
        )

BOOST_FUSION_ADAPT_STRUCT(ast::contents,
        (ast::metadata, _meta)
        (ast::data, _data)
        )

template <typename It>
struct skipper : qi::grammar<It> {
    skipper() : skipper::base_type(start) {
        using namespace qi;
        start = blank | lexeme [ '#' >> *~char_("\n")];
    }
  private:
    qi::rule<It> start;
};

template <typename It, typename Skipper = skipper<It> >
struct grammar : qi::grammar<It, ast::contents(), Skipper>
{
    grammar() : grammar::base_type(contents) {
        using namespace qi;

        quoted = '"' >> *('\\' >> char_ | ~char_('"')) >> '"';

        column_definition = 
            "col" >> int_ >> quoted >> quoted >> quoted >> bool_ >> quoted;

        column_definitions = *eol
            >> column_definition % +eol;

        record = '(' >> quoted >> ',' >> int_ >> ')';

        column_mapping = 
            "map" >> quoted >> record % ',';

        column_mappings = *eol
            >> column_mapping % +eol;

        metadata = column_definitions 
                >> column_mappings 
                ;

        data_row    = repeat(_r1) [ auto_ ];
        data_header = *eol >> repeat(2) [ *~char_("\n") >> +eol ];
        data        = data_header >> data_row(_r1) % +eol;

        auto number_of_columns = phx::size(
                    phx::bind(
                        &ast::metadata::coldefs,
                        phx::bind(&ast::contents::_meta, _val)
                    ));

        contents = metadata >> data(number_of_columns) >> +eol;

        BOOST_SPIRIT_DEBUG_NODES(
                (contents)(metadata)(data)(data_row)(data_header)
                (column_definitions)(column_definition)
                (column_mapping)(column_mappings)(record)
                (quoted)
            );
    }
  private:
    qi::rule<It, ast::contents(),               Skipper> contents;
    qi::rule<It, ast::metadata(),               Skipper> metadata;
    qi::rule<It, ast::column_mapping::record(), Skipper> record;
    qi::rule<It, ast::column_mappings(),        Skipper> column_mappings;
    qi::rule<It, ast::column_mapping(),         Skipper> column_mapping;
    qi::rule<It, ast::column_definitions(),     Skipper> column_definitions;
    qi::rule<It, ast::column_definition(),      Skipper> column_definition;
    qi::rule<It, std::string()>                 quoted;
    // the inherited attribute is the number of column definitions
    qi::rule<It, ast::data::cells::value_type(size_t), Skipper> data_row;
    qi::rule<It, ast::data::cells(size_t),             Skipper> data;
    qi::rule<It,                                       Skipper> data_header;
};

int main() {
    using It = boost::spirit::istream_iterator;

    It f(std::cin >> std::noskipws), l;

    ast::contents parsed;
    bool ok = qi::phrase_parse(f, l, grammar<It>(), skipper<It>(), parsed);

    if (ok) {
        std::cout << "Parse succeeded\n";

        for (auto& coldef : parsed._meta.coldefs)
            std::cout << std::boolalpha << "COL { "
                 << coldef.index    << " "
                 << coldef.alpha_id << " "
                 << coldef.type     << " "
                 << coldef.function << " "
                 << coldef.mapped   << " "
                 << coldef.name     << " }\n";

        for (auto& colmap : parsed._meta.colmaps) {
            std::cout << std::boolalpha << "MAP '" << colmap.alpha_id << "' {\n";
            for (auto& entry : colmap.mappings)
                std::cout << "\t" << entry.first << " -> '" << entry.second << "'\n";
            std::cout << "}\n";
        }

        std::cout << "\ndata\n======================================\n";
        auto& by_idx = parsed._meta.coldefs.get<ast::by_idx>();
        for (auto& row : parsed._data._cells) {
            for (size_t i = 0; i < row.size(); ++i) {
                auto def = by_idx.find(i);
                assert(by_idx.end() != def);

                if (def->mapped) {
                    auto& maps = parsed._meta.colmaps;

                    auto match = std::find_if(maps.begin(), maps.end(),
                            [&](ast::column_mapping const& m) { return m.alpha_id == def->alpha_id; });

                    assert(maps.end() != match);
                    std::cout << std::setw(8) << std::left << (" '" + match->mappings[row[i]] + "'");
                } else {
                    std::cout << std::setw(8) << std::right << row[i];
                }
            }
            std::cout << '\n';
        }

    } else {
        std::cout << "Parse failed\n";
    }

    if (f != l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
