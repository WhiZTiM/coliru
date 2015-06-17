#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>

template <typename Container>
typename Container::value_type find_using_hashTable(const Container& vec){
    using T = typename Container::value_type;
	std::unordered_map<T, int> hashTable;
	for (const auto& elem : vec){
		hashTable[elem]++;
	}
	T min = std::numeric_limits<T>::max();
	for (const auto& elem : vec){
		if (elem<min && hashTable[elem]>1)
			min = elem;
	}
	return min;
}

template <typename Container>
typename Container::value_type findSmallestNonunique(Container c)
{
	std::sort(std::begin(c), std::end(c));
	auto it = std::adjacent_find(std::begin(c), std::end(c));

	if (it == std::end(c))
		return std::numeric_limits<typename Container::value_type >::max();

	return *it;
}


int  main(){
	const int MaxArraySize = 5000100;
	const int minArraySize = 5000000;
	const int numberOfTests = 3;

	//std::ofstream file;
	//file.open("test.txt");
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(0,30000000);

	for (int t = minArraySize; t < MaxArraySize; t++){
		double avg = 0,avg2=0;
		for (int n = 0; n < numberOfTests; n++){
			std::vector<int> vec;
			vec.reserve(t);
			for (int i = 0; i < t; i++){//por kardan array ba anasor random
				vec.push_back(distribution(generator));
			}
			//method1
			auto start = std::chrono::steady_clock::now();
			int val = find_using_hashTable(vec);
			auto end = std::chrono::steady_clock::now();
			avg += std::chrono::duration <double, std::nano>(end-start).count();
		//	std::cout << val<<" ";
			//method2
			start = std::chrono::steady_clock::now();
			val = findSmallestNonunique(vec);
			end = std::chrono::steady_clock::now();
			avg2 += std::chrono::duration <double, std::nano>(end - start).count();
		//	std::cout << val<<" ";
		}
		//file << avg/numberOfTests <<" "<<avg2/numberOfTests<<'\n';
		//file << "__\n";
		std::cout <<"Method1 : "<<
			avg / numberOfTests << " Method2 : " << avg2 / numberOfTests << '\n';
	}

}