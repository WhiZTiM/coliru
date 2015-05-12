#include <iostream>
#include <vector>

struct sometype {
    sometype(int val) : value(val) {}
	int value;
};

class Wrapper
{
private:
	std::vector<sometype> *_data;
public:
	std::vector<sometype>& data() { return *_data; } // Add some sanity checks here
	const std::vector<sometype>& data() const { return *_data; }
	//... other stuff
	Wrapper(std::vector<sometype> *vec) : _data(vec) {}
};


void bar(std::vector<std::vector<sometype>>& par) {
	for (auto& subvec : par) {
		for (auto& sometypeItem : subvec) {
			std::cout << sometypeItem.value;
		}
	}
}

int main(int argc, char ** argv)
{

	std::vector<std::vector<sometype>> vec;
	std::vector<Wrapper> internalVec;

	vec.emplace_back();
	internalVec.emplace_back(&(vec[0]));
	internalVec[0].data().emplace_back(42); // Constructs a sometype

	vec.emplace_back();
	internalVec.emplace_back(&(vec[1]));
	internalVec[1].data().emplace_back(52); // Constructs a sometype
	
	bar(vec);


	return 0;
}