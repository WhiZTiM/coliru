#ifndef ATLAS_HPP
#define ATLAS_HPP

#include <pugixml/pugixml.hpp>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>

namespace atlasviewer {

class Atlas {
    struct Region { int ax, ay, x, y, w, h; };
    using Pieces = std::vector<Region>;
    std::map<std::string, Pieces> data;

public:
    Atlas (std::string const& path) { 
        pugi::xml_document doc;
        auto result = doc.load_file( "tree.xml" );
        if (!result)
            throw std::runtime_error("Cannot open XML file");

        for (auto asset : doc.children("asset")) {
            Pieces pieces;
            for (auto region : asset.children("rect")) {
                pieces.emplace_back(
                    region.attribute("ax").as_int(),
                    region.attribute("ay").as_int(),
                    region.attribute("x").as_int(),
                    region.attribute("y").as_int(),
                    region.attribute("w").as_int(),
                    region.attribute("h").as_int()
                );
            }
            data.emplace(asset.attribute("id").as_string(), pieces);
        }
    }
};

}

#endif ATLAS_HPP