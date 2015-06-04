#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include <set>
#include <exception>
#include <random>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <chrono>



struct Customer
{
    int mobileNo;
    std::string name;
};


struct Table
{
    std::string m_tableId;
    int m_numSeats;
    bool m_available;
    Customer m_customer;

    Table( std::string tableId, int numSeats, bool available, Customer c)
        : m_tableId(std::move(tableId))
        , m_numSeats(numSeats)
        , m_available(available)
        , m_customer(std::move(c))
    { }

    Table() { }


    bool operator<(const Table& t)
    {
        return m_numSeats < t.m_numSeats;
    }
};

struct Restaurant
{
    std::vector<Table> m_tables;
};


struct Restaurant_H
{
    std::unordered_map<int, std::vector<Table>> tableMap;
};



struct Comp
{
    bool operator()(const Table& t, int numseats) const
    {
        return t.m_numSeats < numseats;
    }

    bool operator()(int numseats, const Table& t) const
    {
        return numseats < t.m_numSeats;
    }
};


typedef std::chrono::high_resolution_clock Clock;

struct Timer
{

	typedef std::chrono::time_point<Clock> TimePoint;
	TimePoint m_start;
	std::string m_msg;
	std::ostream& m_os;

	Timer(std::string const& msg, std::ostream& os)
	: m_start { Clock().now() }
	, m_msg { msg }
	, m_os { os }
	{ 
	}

	~Timer()
	{
		auto finish = Clock().now();
		m_os << m_msg << ",took:" << std::chrono::duration_cast<std::chrono::milliseconds>(finish - m_start).count() << "ms\n";
	}
};

template<typename Func, typename... Args>
auto TimeTaken(std::ostream& os, std::string const& msg, Func&& f, Args&& ...args) -> decltype(f(os, msg, std::forward<Args>(args)...))
{
	//static_assert(!std::is_same<decltype(f(os, msg, std::forward<Args>(args)...)), void>::value, "functions returning void are not allowed");
	Timer t{ msg, os };
    return f(os, msg, std::forward<Args>(args)...);
}

int UsingHashMap(std::ostream& os, std::string const& msg, const Restaurant_H& r, const std::unordered_set<int>& numseats)
{
	int count = 0;
	char str[256] = { '\0' };
	for (int seats : numseats)
	{
		memset(str, '\0', 256);
		auto iter = r.tableMap.find(seats);
		if (iter != r.tableMap.end())
		{
			sprintf(str, "Asked for:%d seats and got...\n", seats);
	//		os.write(str, strlen(str));
			for (auto&& t : iter->second)
			{
				if (t.m_available)
				{
					memset(str, '\0', 256);
					sprintf(str, "TableId:%s,numseats:%d,available:%s\n", t.m_tableId.c_str(), t.m_numSeats, t.m_available ? "Yes" : "No");
				//	os.write(str, strlen(str));
				}
			}
		}
	}
	return count;
}

int UsingVector(std::ostream& os, std::string const& msg, const Restaurant& r, const std::unordered_set<int>& numseats)
{
	int count = 0;
	char str[256] = { '\0' };
	for (int seats : numseats)
	{
		memset(str, '\0', 256);
		auto p = std::equal_range(r.m_tables.begin(), r.m_tables.end(), seats, Comp());
		sprintf(str, "Asked for:%d seats and got...\n", seats);
	//	os.write(str, strlen(str));
		for (auto i = p.first; i != p.second; ++i)
		{
			if (i->m_available)
			{
				memset(str, '\0', 256);
				sprintf(str, "TableId:%s,numseats:%d,available:%s\n", i->m_tableId.c_str(), i->m_numSeats, i->m_available ? "Yes" : "No");
				// os.write(str, strlen(str));
			}
		}
	}
	return count;
}

int main()
{

 /*
  *  Set up the data.
  * Idea is to generate table ids in the following manner.
  * A01 A02 .... A100 .... Z199
  * In that pattern setup around 5000 tables 
  * For each table randomly set the number of seats and availability or unavailability.
  * Load this information in a vector and then sort the vector on number of seats.
  * Load this information in a hash map with key as number of seats.
  * Create another vector of 5000 elements with randomized number of seats along with the data.
  * Now loop through the vector of number of seats and query the tables in vector and hash map, based on seats and availability 
  * Calculate the time taken for vector and hash map and then you are in for a surprise.
  */
  

    std::random_device rd;
    std::uniform_int_distribution<int> dist_d(1, 40000);
    std::uniform_int_distribution<int> dist_c(1, 26);    
    std::string alphabets{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    std::set<std::string> table_set;

    while (table_set.size() < 500000)
    {
        int c = dist_c(rd);
        int d = dist_d(rd);
        table_set.insert((alphabets[c] == '\0' ? 'A' : alphabets[c]) + std::to_string(d));      
    }

	std::cout << "Table set up complete\n";
	

    Restaurant r;
	Restaurant_H rh;
    std::unordered_set<int> numseats_random;

    std::uniform_int_distribution<int> dist_t(3, 20);
    std::uniform_int_distribution<int> dist_a(0,1);
    for (auto const& s : table_set)
    {
        int numseats = dist_t(rd);
		bool available = dist_a(rd) == 0 ? false : true;
        r.m_tables.emplace_back(s, numseats, available, Customer{ 1234, "XYZ" });
		rh.tableMap[numseats].emplace_back(s, numseats, available, Customer{ 1234, "XYZ" });
		numseats_random.insert(numseats);
    }

    std::sort(r.m_tables.begin(), r.m_tables.end(), [] (const Table& l, const Table& r)
    {
        return l.m_numSeats < r.m_numSeats;
    });

	std::cout << "Test data set up complete\n";
	std::cout << "Table contains:" << r.m_tables.size() << " elements\n";
	long count = 0;
	for (auto&& p : rh.tableMap)
	{
		count += p.second.size();
	}

	std::cout << "Hash Map contains:" << count << " elements\n";
    
   // std::ofstream outfile_v("output_v.txt");
//    std::ofstream outfile_h("output_h.txt");

std::ostream& outfile_v = std::cout;
std::ostream& outfile_h = std::cout;


	TimeTaken(outfile_v, "Using vector...", UsingVector, r, numseats_random);
	TimeTaken(outfile_h, "Using hash map...", UsingHashMap, rh, numseats_random);
	TimeTaken(outfile_v, "Using vector...", UsingVector, r, numseats_random);
	TimeTaken(outfile_h, "Using hash map...", UsingHashMap, rh, numseats_random);
	TimeTaken(outfile_h, "Using hash map...", UsingHashMap, rh, numseats_random);
	TimeTaken(outfile_v, "Using vector...", UsingVector, r, numseats_random);
	TimeTaken(outfile_h, "Using hash map...", UsingHashMap, rh, numseats_random);
	TimeTaken(outfile_v, "Using vector...", UsingVector, r, numseats_random);
}


