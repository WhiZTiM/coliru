#include <string>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

//fibonacci heap
#include <boost/heap/fibonacci_heap.hpp>


#include <fstream>
#include <cstring>
#include <iostream>
#include <unordered_map>

using namespace std;

//TESTER
// Globalne premenne

const unsigned int MAX_POCET_SKUPIN_TESTOV = 5;
unsigned int pocetSkupin = 0;
unsigned int aktualnaSkupina = 0;
string nazvySkupin[MAX_POCET_SKUPIN_TESTOV];
unsigned int pocetTestovSkupiny[MAX_POCET_SKUPIN_TESTOV];
unsigned int pocetZlyhanychTestovSkupiny[MAX_POCET_SKUPIN_TESTOV];

void pridajZbehnutyTest(bool vysledok) {
  pocetTestovSkupiny[aktualnaSkupina] += 1;
  if (vysledok == false) {
    pocetZlyhanychTestovSkupiny[aktualnaSkupina] += 1;
  }
}
int getPocetTestov() {
  return pocetTestovSkupiny[aktualnaSkupina];
}
string vysledokTestu(bool vysledok) {
  return vysledok ? " - OK" : " - FALSE";
}
string getNazovSkupiny() {
  return nazvySkupin[aktualnaSkupina];
}
int getPocetZlyhanychTestov() {
  return pocetZlyhanychTestovSkupiny[aktualnaSkupina];
}
void nastavSledovanieSkupiny(const string nazov) {
  if (pocetSkupin < MAX_POCET_SKUPIN_TESTOV) {
    pocetSkupin += 1;
  }
  aktualnaSkupina = pocetSkupin - 1;
  nazvySkupin[aktualnaSkupina] = nazov;
  pocetTestovSkupiny[aktualnaSkupina] = 0;
  pocetZlyhanychTestovSkupiny[aktualnaSkupina] = 0;
  cout << endl << "<----------" << getNazovSkupiny() << "---------->" << endl;
}
void zhodnotenieVysledkov(){
  cout << "<--- " << getNazovSkupiny();
  cout << " (" << getPocetTestov() << ":" << getPocetZlyhanychTestov() << ")";
  bool vysledok = (getPocetZlyhanychTestov() == 0) ? true : false;
  cout << vysledokTestu(vysledok) << endl << endl;
}
bool testTrue(bool vysledok, const string nazovTestu){
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testFalse(bool vysledok, string nazovTestu){
  return testTrue(!vysledok, nazovTestu);
}
bool testEqual(int i1, int i2, const string nazovTestu){
  bool vysledok = (i1 == i2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << i1 << "'=='" << i2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testNonEqual(int i1, int i2, const string nazovTestu){
  bool vysledok = (i1 != i2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << i1 << "'!='" << i2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testEqual(double d1, double d2, const string nazovTestu){
  bool vysledok = (d1 == d2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << d1 << "'=='" << d2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testNonEqual(double d1, double d2, const string nazovTestu){
  bool vysledok = (d1 != d2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << d1 << "'!='" << d2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testEqual(const string s1, const string s2, const string nazovTestu){
  bool vysledok = (s1 == s2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << s1 << "'=='" << s2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testNonEqual(const string s1, const string s2, const string nazovTestu){
  bool vysledok = (s1 != s2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << s1 << "'!='" << s2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
int pocetSkupinTestov() {
  return pocetSkupin;
}
string getNazovDanejSkupiny(unsigned int cislo) {
  if (cislo < pocetSkupin) {
    return nazvySkupin[cislo];
  }
  return "";
}
int pocetTestovDanejSkupiny(unsigned int cislo) {
  if (cislo < pocetSkupin) {
    return pocetTestovSkupiny[cislo];
  }
  return 0;
}
int pocetNesplnenychTestovDanejSkupiny(unsigned int cislo) {
  if (cislo < pocetSkupin) {
    return pocetZlyhanychTestovSkupiny[cislo];
  }
  return 0;
}
void zhodnotenieTestov(){
  unsigned int pocetVsetkychTestov = 0;
  unsigned int pocetVsetkychNesplnenychTestov = 0;
  cout << "<----------- Zaverecne zhodnotenie ---------->" << endl;
  for (unsigned int i = 0; i < pocetSkupin; i++) {
    cout << "       " << i + 1 << ": " << nazvySkupin[i];
    cout << " (" << pocetTestovDanejSkupiny(i) << ":" << pocetNesplnenychTestovDanejSkupiny(i) << ")";
    cout << endl;
    pocetVsetkychTestov += pocetTestovDanejSkupiny(i);
    pocetVsetkychNesplnenychTestov += pocetNesplnenychTestovDanejSkupiny(i);
  }
  cout << endl << "       Celkovy vysledok";
  cout << " (" << pocetVsetkychTestov << ":" << pocetVsetkychNesplnenychTestov << ")";
  bool vysledok = (pocetVsetkychNesplnenychTestov == 0) ? true : false;
  cout << vysledokTestu(vysledok) << endl << endl;
}
// END TESTER



/// @brief The usual PI/180 constant  
static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
/// @brief Earth's quatratic mean radius for WGS-84  
static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

struct HranaSerial {
    uint64_t kam;
	double vzdialenost;
	int ohodnotenie_poi;
	double kam_lon;
	double kam_lat;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(kam_lon, kam_lat, kam, vzdialenost, ohodnotenie_poi);
	}

	HranaSerial(){}
	HranaSerial(uint64_t _kam, double _vzdialenost){ //pre testovanie
		kam = _kam;
		vzdialenost = _vzdialenost;
	}
};


struct Vrchol {
	uint64_t id;
	double priorita;

	Vrchol(uint64_t osmid, double p) :id(osmid), priorita(p){}

};

struct compare_vrchol
{
	bool operator()(const Vrchol& n1, const Vrchol& n2) const
	{
		return n1.priorita > n2.priorita;
	}

};

class HladanieCesty{
private:
	std::unordered_map<uint64_t, std::vector<HranaSerial>> graf; //odkial : kam,vzdialenost,ohodnotenie_poi
public:
double ArcInRadians(const  boost::tuple<double, double> &from, const  boost::tuple<double, double> &to) {
		double latitudeArc = (from.get<1>() - to.get<1>()) * DEG_TO_RAD;
		double longitudeArc = (from.get<0>() - to.get<0>()) * DEG_TO_RAD;
		double latitudeH = sin(latitudeArc * 0.5);
		latitudeH *= latitudeH;
		double lontitudeH = sin(longitudeArc * 0.5);
		lontitudeH *= lontitudeH;
		double tmp = cos(from.get<1>()*DEG_TO_RAD) * cos(to.get<1>()*DEG_TO_RAD);
		return 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH));
	}

	/** @brief Computes the distance, in meters, between two WGS-84 positions.
	*
	* The result is equal to <code>EARTH_RADIUS_IN_METERS*ArcInRadians(from,to)</code>
	*
	* @sa ArcInRadians
	*/
	double DistanceInMeters(const  boost::tuple<double, double>& from, const  boost::tuple<double, double>& to) {
		return EARTH_RADIUS_IN_METERS*ArcInRadians(from, to);
	}


	double heuristic(HranaSerial &h, double &b_lon, double &b_lat) {
		boost::tuple<double, double> t1 = boost::make_tuple(h.kam_lon, h.kam_lat);
		boost::tuple<double, double> t2 = boost::make_tuple(b_lon, b_lat);

		double vzdialenost = DistanceInMeters(t1, t2);

		return vzdialenost;
	}

	double heuristic_test(unordered_map<uint64_t, uint64_t> &mapa_heuristika, uint64_t &odkial) {
		return mapa_heuristika.find(odkial)->second;
	}

	void setGraf(unordered_map<uint64_t, std::vector<HranaSerial>> &_graf){ //kvoli testovaniu
		graf = _graf;
	}
    
    
       
	unordered_map<uint64_t, uint64_t> a_star_search_shortest_fib(uint64_t start, uint64_t goal, bool test = false,
		unordered_map<uint64_t, uint64_t> mapa_heuristika = unordered_map<uint64_t, uint64_t>()) //default hladaj najzaujimavejsiu
	{
		typedef boost::heap::fibonacci_heap<Vrchol, boost::heap::compare<compare_vrchol>>::handle_type  handle_t;
		unordered_map<uint64_t, uint64_t>came_from;
		unordered_map<uint64_t, std::tuple<double, handle_t>>cost_so_far_shortest; //cena_do_hrany,boost_fibonacci:handle
		boost::heap::fibonacci_heap<Vrchol, boost::heap::compare<compare_vrchol>> heap;

		handle_t t = heap.push(Vrchol(start, 0));
		came_from[start] = start;
		cost_so_far_shortest[start] = std::make_tuple(0, t);

		//get coordinates from DB
        /*
		const int64_t n_id = static_cast<int64_t>(goal);
		mongo::BSONObj p = BSON("_id" << n_id);
		double goal_lon;
		double goal_lat;
		auto_ptr<mongo::DBClientCursor> cursor = mongo.query("data.vrcholy", p);
		while (cursor->more()) {
			mongo::BSONObj p = cursor->next();
			std::vector<mongo::BSONElement> loc = p["loc"].Array();
			goal_lon = loc[0].Double();
			goal_lat = loc[1].Double();
		}
        */

		while (!heap.empty()) {
			auto current = heap.top();
			heap.pop();

			if (current.id == goal) {
				break;
			}

			for (auto hrana : graf[current.id]) {
				double	new_cost = std::get<0>(cost_so_far_shortest[current.id]) + hrana.vzdialenost;

				unordered_map<uint64_t, std::tuple<double, handle_t>>::iterator iter = cost_so_far_shortest.find(hrana.kam);
				bool existuje_v_halde = (iter != cost_so_far_shortest.end());

				if (!existuje_v_halde || new_cost < std::get<0>(cost_so_far_shortest[hrana.kam])) {
					std::get<0>(cost_so_far_shortest[hrana.kam]) = new_cost; //nastav novu dlzku cesty
					double priority;
					if (test){
						priority = new_cost + heuristic_test(mapa_heuristika, hrana.kam);
					}
                    /*
					else{
						priority = new_cost + heuristic(hrana, goal_lon, goal_lat);
					}
                    */

					if (existuje_v_halde) { //ak nasiel,tak zvys prioritu
						handle_t povodny = std::get<1>(cost_so_far_shortest[hrana.kam]);
						if ((*povodny).priorita > priority){
							cout << "Increase(lower priority) for " << hrana.kam << " from " << (*povodny).priorita << " to " << priority << endl;
							(*povodny).priorita = priority;
							heap.increase(povodny); //zniz prioritu	
						}
						else{
							cout << "Decrease(raise priority) for " << hrana.kam << " from " << (*povodny).priorita << " to " << priority << endl;
							(*povodny).priorita = priority;
							heap.decrease(povodny);
						}

					}
					else {
						handle_t novy = heap.push(Vrchol(hrana.kam, priority));
						std::get<1>(cost_so_far_shortest[hrana.kam]) = novy;
						cout << "Pushed " << hrana.kam << " with priority " << priority << endl;
					}

					came_from[hrana.kam] = current.id;
				}

			}
		}


		cout << "Dlzka cesty " << std::get<0>(cost_so_far_shortest[goal]) << endl;


		return came_from;
	}
std::vector<uint64_t> reconstruct_path_ids(
		uint64_t start,
		uint64_t goal,
		unordered_map<uint64_t, uint64_t>& came_from
		) {
		vector<uint64_t> path;
		uint64_t current = goal;
		path.push_back(current);
		while (current != start) {
			current = came_from[current];
			path.push_back(current);
		}
		return path;
	}

};




int main()
{
    
    nastavSledovanieSkupiny("Testy pre A* s pouzitim std::priority queue a boost::fibonacci_heap ");
    
   std::unordered_map<uint64_t, std::vector<HranaSerial>> graf;
    graf[0].push_back(HranaSerial{1,3});
	graf[0].push_back(HranaSerial{ 2, 5 });

	graf[1].push_back(HranaSerial{ 2, 4 });
	graf[1].push_back(HranaSerial{ 6, 7 });

	graf[2].push_back(HranaSerial{ 0, 2 });
	graf[2].push_back(HranaSerial{ 1, 1 });
	graf[2].push_back(HranaSerial{ 4, 1 });
	graf[2].push_back(HranaSerial{ 3, 16 });

	graf[3].push_back(HranaSerial{ 0, 9 });
	graf[3].push_back(HranaSerial{ 5, 3 });

	graf[4].push_back(HranaSerial{ 1,1});
	graf[4].push_back(HranaSerial{ 2, 1 });
	graf[4].push_back(HranaSerial{ 3, 7 });
	graf[4].push_back(HranaSerial{ 6, 1 });

	graf[5].push_back(HranaSerial{ 6, 4 });

	HladanieCesty hladanie;
	hladanie.setGraf(graf);

	unordered_map<uint64_t, uint64_t> mapa_heuristika;
	mapa_heuristika[0] = 6;
	mapa_heuristika[1] = 6;
	mapa_heuristika[2] = 2;
	mapa_heuristika[3] = 7;
	mapa_heuristika[4] = 1;
	mapa_heuristika[5] = 3;
	mapa_heuristika[6] = 0;


	unordered_map<uint64_t, uint64_t> came_from = hladanie.a_star_search_shortest_fib(0, 6, true,mapa_heuristika);
	std::vector<uint64_t> cesta = hladanie.reconstruct_path_ids(0, 6, came_from);

	std::stringstream ss2;
	std::copy(cesta.begin(), cesta.end() - 1,
		std::ostream_iterator<int>(ss2, ","));

	// Now add the last element with no delimiter
	ss2 << cesta.back();

	testEqual("6,4,2,0", ss2.str(), "Spravna cesta fibonacci heap");



	//TEST ZMENA PRIORITY
	std::unordered_map<uint64_t, std::vector<HranaSerial>> graf2;
	graf2[0].push_back(HranaSerial{ 1, 7 });
	graf2[0].push_back(HranaSerial{ 2, 5 });

	graf2[1].push_back(HranaSerial{ 2, 4 });
	graf2[1].push_back(HranaSerial{ 6, 7 });  

	graf2[2].push_back(HranaSerial{ 0, 2 });
	graf2[2].push_back(HranaSerial{ 1, 1 });
	graf2[2].push_back(HranaSerial{ 4, 3 });
	graf2[2].push_back(HranaSerial{ 3, 4 });

	graf2[3].push_back(HranaSerial{ 0, 9 });
	graf2[3].push_back(HranaSerial{ 5, 3 });

	graf2[4].push_back(HranaSerial{ 1, 1 });
	graf2[4].push_back(HranaSerial{ 2, 1 });
	graf2[4].push_back(HranaSerial{ 3, 7 });
	graf2[4].push_back(HranaSerial{ 6, 8 });

	graf2[5].push_back(HranaSerial{ 6, 1 });

	hladanie.setGraf(graf2);

	unordered_map<uint64_t, uint64_t> mapa_heuristika2;
	mapa_heuristika2[0] = 12;
	mapa_heuristika2[1] = 6;
	mapa_heuristika2[2] = 7;
	mapa_heuristika2[3] = 3;
	mapa_heuristika2[4] = 7;
	mapa_heuristika2[5] = 0;
	mapa_heuristika2[6] = 0;

	unordered_map<uint64_t, uint64_t> came_from2 = hladanie.a_star_search_shortest_fib(0, 6, true, mapa_heuristika2);
	std::vector<uint64_t> cesta2 = hladanie.reconstruct_path_ids(0, 6, came_from2);

	std::stringstream ss4;
	std::copy(cesta2.begin(), cesta2.end() - 1,
		std::ostream_iterator<int>(ss4, ","));

	// Now add the last element with no delimiter
	ss4 << cesta2.back();

	testEqual("6,1,2,0", ss4.str(), "Spravna cesta fibonacci heap");
    
    
    nastavSledovanieSkupiny("Testy pre boost::fibonacci_heap ");

    typedef boost::heap::fibonacci_heap<Vrchol, boost::heap::compare<compare_vrchol>>::handle_type  handle_t;
	unordered_map<uint64_t, handle_t>vrchol_handle;
	boost::heap::fibonacci_heap<Vrchol, boost::heap::compare<compare_vrchol>> heap;

	handle_t novy = heap.push(Vrchol(1, 1));
	vrchol_handle.insert(make_pair(1, novy));

	handle_t novy2 = heap.push(Vrchol(2,5));
	vrchol_handle.insert(make_pair(2, novy2));

	handle_t novy3 = heap.push(Vrchol(3, 7));
	vrchol_handle.insert(make_pair(3, novy3));

	handle_t novy4 = heap.push(Vrchol(4, 9));
	vrchol_handle.insert(make_pair(4, novy4));

	handle_t novy5 = heap.push(Vrchol(5, 13));
	vrchol_handle.insert(make_pair(5, novy5));

	(*vrchol_handle[5]).priorita = 8;
	heap.increase(vrchol_handle[5]);

	(*vrchol_handle[2]).priorita = 13;
	heap.decrease(vrchol_handle[2]);

	(*vrchol_handle[3]).priorita = 8;
	heap.decrease(vrchol_handle[3]);

stringstream s;
    while (!heap.empty()){
		auto v = heap.top();
		heap.pop();
		if (!heap.empty()){
			s << v.id << ",";
		}
		else{
			s << v.id;
		}		
	}

	testEqual("1,3,5,4,2", s.str(), "Test fibonacci heap");
    
    
    zhodnotenieVysledkov();
}
