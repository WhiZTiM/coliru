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


typedef bmi::multi_index_container<
    QTableElem,
	bmi::indexed_by<
		bmi::ordered_unique<bmi::member<QTableElem,int,&QTableElem::dummy> >
	>
> QTable;
 
int main()
{
	using boost::serialization::make_nvp;
	{
		std::ofstream out("test.xml");
		boost::archive::xml_oarchive oa(out);

        QTable obj;
		oa << make_nvp("graph", obj);
	}

	try {
		std::ifstream xml("test.xml");
		boost::archive::xml_iarchive ia(xml);
		QTable obj;
            ia >> make_nvp("graph", obj); 
	} catch (boost::archive::archive_exception const& ae) {
		std::cout << "Error: " << ae.code << ":'" << ae.what() << "'\n";
	}
}
