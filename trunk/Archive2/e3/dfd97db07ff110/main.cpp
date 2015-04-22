#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/algorithm/string.hpp>

int main()
{
    using namespace std;
    using namespace boost;
    using namespace boost::accumulators;

    ifstream inNew("C:/Users/A.csv");
    size_t columns = 3;
    vector<accumulator_set<double, stats<tag::mean, tag::variance>>> acc(columns);

    if (inNew)
    {
        string line;
        while (getline(inNew, line))
        {
            vector<string> strs;
            split(strs, line, is_any_of("\t ,"));
            if (strs.size() == columns)
            {
                for (size_t i = 0; i < columns; ++i)
                {
                    acc[i](stod(strs[i]));
                }
            }
        }

        for (size_t i = 0; i < columns; ++i)
        {
            cout << "Stats for column " << (i + 1) << endl;
            cout << "Expected return is: " << mean(acc[i]) << endl;
            cout << "Variance: " << variance(acc[i]) << endl;
            cout << "Std Dev: " << sqrt(variance(acc[i])) << endl;
        }
    }

    inNew.close();

    system("pause");
    return 0;
}