#include <iostream>
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

namespace bmi = boost::multi_index;

struct QTableElem {
    template<class Archive> void serialize(Archive &ar,const unsigned int) {
		ar & boost::serialization::make_nvp("dummy", dummy);
	}
	int dummy;
};

class QTable : public bmi::multi_index_container<
	QTableElem,
	bmi::indexed_by<
		bmi::ordered_unique<bmi::member<QTableElem,int,&QTableElem::dummy> >
	>
> {};

 
int main()
{
	using boost::serialization::make_nvp;
	{
		QTable obj;
		std::ofstream out("test.xml");
		if (false == out.is_open()) throw std::runtime_error("invalid file!");
		boost::archive::xml_oarchive oa(out);
		oa << make_nvp("graph", obj);
	}

	{
		std::ifstream xml("test.xml");
		boost::archive::xml_iarchive ia(xml);
		QTable obj;
		try { ia >> make_nvp("graph", obj); }
		catch (boost::archive::archive_exception const& ae) {
			std::cout << "Error: " << ae.code << ":'" << ae.what() << "'\n";
		}
	}
}
