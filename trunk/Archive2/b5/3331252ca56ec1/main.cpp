#include <iostream>
#include <vector>

using namespace std;

class Wrapper
{
    private:
	    std::vector<int> *_data;
    public:
    	std::vector<int>& data() { return *_data; } // Add some sanity checks here
    	const std::vector<int>& data() const { return *_data; }
	    //... other stuff
	    Wrapper(std::vector<int> *vec) : _data(vec) {}
};


void bar(std::vector<std::vector<int>>& par)
{
	for (auto& subvec : par) {
		for (auto& sometypeItem : subvec) {
			std::cout << sometypeItem<< endl;
		}
	}
    std::vector<int> v1 = { 1,2,3 };
    par.push_back(v1);

}

int main(int argc, char ** argv)
{

	std::vector<std::vector<int>> vec;
	std::vector<Wrapper> internalVec;

	vec.emplace_back();
	internalVec.emplace_back(&(vec[0]));
	internalVec[0].data().emplace_back(42); // Constructs a sometype

	vec.emplace_back();
	internalVec.emplace_back(&(vec[1]));
	internalVec[1].data().emplace_back(52); // Constructs a sometype

    cout << "vec1 size=" << vec.size() << " vec2 size=" << internalVec.size() << endl;

	bar(vec);

    cout << "vec2 size=" << vec.size() << " vec2 size=" << internalVec.size() << endl;

	return 0;
}