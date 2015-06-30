    #include <algorithm>
    #include <vector>
    #include <set>
    #include <iostream>
    #include <iterator>
    
    using namespace std;
    
    std::set<std::vector<int>> getSubsets(const std::vector<int>& vect, size_t numToChoose)
    {
        std::set<std::vector<int>> returnVal;
        // return the whole thing if we want to
        // choose everything 
        if (numToChoose >= vect.size())
        {
            returnVal.insert(vect);
            return returnVal;
        }
    
        // set up bool vector for combination processing
        std::vector<bool> bVect(vect.size() - numToChoose, false);

        // stick the true values at the end of the vector
        bVect.resize(bVect.size() + numToChoose, true); 
    
        // select where the ones are set in the bool vector and populate
        // the combination vector
        do
        {
            std::vector<int> combination;
            for (size_t i = 0; i < bVect.size() && combination.size() <= numToChoose; ++i)
            {
                if (bVect[i])
                    combination.push_back(vect[i]);
            }
            // sort the combinations
            std::sort(combination.begin(), combination.end());
    
            // insert this new combination in the set
            returnVal.insert(combination);
        } while (next_permutation(bVect.begin(), bVect.end()));
        return returnVal;
    }
    
    int main()
    {
        std::vector<int> myVect = {1,2,2,3,3,3,3};
    
        // number to select
        size_t numToSelect = 3;
    
        // get the subsets
        std::set<std::vector<int>> subSets = getSubsets(myVect, numToSelect);
    
        // output the results
        for_each(subSets.begin(), subSets.end(), [] (const vector<int>& v) 
        { cout << "subset "; copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); cout << "\n"; });
    }