#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <boost/ptr_container/ptr_vector.hpp>

struct Property {
    virtual ~Property() = default;

    void setOwner(std::string) {}
    void setAddress(std::string) {}
    void setSuburb(std::string) {}
    void setPostcode(int) {}

    virtual std::string getType() const { return "Property"; }
};

struct Residential : Property {
    void setBedrooms(int) {}
    virtual std::string getType() const { return "Residential"; }
};

template <typename T> T changeString(std::string const& s) {
    return boost::lexical_cast<T>(s);
}

struct ResSales : Residential {
    void setAuctionDate(std::string) {}
    void setPrice(double) {}
    virtual std::string getType() const { return "ResSales"; }
};
struct ResRentals : Residential {
    void setBond(double) {}
    void setMonthlyRent(double) {}
    virtual std::string getType() const { return "ResRentals"; }
};

struct PropertyContainer {
    void addProperty(Property* p) {
        _properties.push_back(p);
    }

    boost::ptr_vector<Property> _properties;
};

template <typename Token>
bool validate(int, Token const&) {
    return true; // TODO
}

bool loadProperties(char const *residential, char const *commercial, PropertyContainer *thePropertyContainer) {

    std::ifstream propertyFile(residential);
    int datapos = 6;
    Property *propertyType = NULL;

    if (!propertyFile.is_open()) {
        std::cout << "Cant open file: " << residential << std::endl;
        return false;
    }

    std::string buffer;
    while (propertyFile.good()) {

        std::getline(propertyFile, buffer);

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> sep("\n\t\0,*");
        tokenizer tokens(buffer, sep);

        for (tokenizer::iterator pos = tokens.begin(); pos != tokens.end(); ++pos) {

            if (!validate(datapos, *pos)) {
                return false;
            }

            switch (datapos) {
            case 6:
                {
                    std::vector<std::string> splitstring;
                    boost::split(splitstring, *pos, boost::is_any_of(" ")); //<------(LINE 129) this is where I am trying to split via white space for a second time.
                    if (splitstring[0] == "RS") {
                        propertyType = new ResSales;
                    }
                    else if (splitstring[0] == "RS") {
                        propertyType = new ResRentals;
                    }
                    else {
                        return false;
                    }
                }
                break;
            case 7:
                propertyType->setOwner(*pos);
                break;
            case 8:
                propertyType->setAddress(*pos);
                break;
            case 9:
                propertyType->setSuburb(*pos);
                break;
            case 10:
                propertyType->setPostcode(changeString<int>(*pos));
                break;
            case 11:
                dynamic_cast<Residential *>(propertyType)->setBedrooms(changeString<int>(*pos));
                break;
            case 12:
                if (propertyType->getType() == "ResSales") {
                    dynamic_cast<ResSales *>(propertyType)->setAuctionDate(*pos);

                } else if (propertyType->getType() == "ResRentals") {
                    dynamic_cast<ResRentals *>(propertyType)->setBond(changeString<double>(*pos));
                }
                break;
            case 13:
                if (propertyType->getType() == "ResSales") {
                    dynamic_cast<ResSales *>(propertyType)->setPrice(changeString<double>(*pos));

                } else if (propertyType->getType() == "ResRentals") {
                    dynamic_cast<ResRentals *>(propertyType)->setMonthlyRent(changeString<double>(*pos));
                }
                break;
            }

            if (datapos >= 14) {
                thePropertyContainer->addProperty(propertyType);
                datapos = 6;
            } else {
                ++datapos;
            }
        }
    }

    propertyFile.close();
    return true;
}

int main() {
    PropertyContainer database;
    loadProperties("input.txt", nullptr /*unused now*/, &database);

    for (auto& p : database._properties) {
        std::cout << p.getType() << "\n";
    }
}
