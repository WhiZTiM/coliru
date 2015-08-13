#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
        
using namespace std;

vector<string> words { "Jagan", "Jagan", "Jagan", "Jagan", "Naren", "Naren", "Naren", "Kishore", "Kishore", "Ramesh" };

typedef unordered_map<string, int> WordsMap;
WordsMap wordsMap;

for (auto const& word: words)
{
    wordsMap[word]++;
}


typedef pair<string, int> WordFrequency;



auto compare = [](WordFrequency const& lhs, WordFrequency const& rhs)
{
	return lhs.second < rhs.second;
};

typedef decltype(compare) Comparer;

priority_queue<WordFrequency, vector<WordFrequency>, Comparer> pq(compare);

for(auto const& wf : wordsMap)
{
	pq.push(wf);
}


int count = 0;
while (!pq.empty() && count != 3)
{
	const auto& wf = pq.top();
    std::cout << wf.first << "->" << wf.second << '\n';
    pq.pop();
    ++count;
}

    
    
}
