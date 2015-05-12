#include <iostream>
#include <vector>

struct sometype {
    int value;
    sometype(int v) : value(v) {}
};

void bar(std::vector<std::vector<sometype>>& par) {

    std::cout << "bar() - Before adding new elements:" << std::endl;
    for (auto& subvec : par) {
        std::cout << "Subvector: {";
        for (auto& sometypeItem : subvec) {
            std::cout << sometypeItem.value << " ";
        }
        std::cout << "};" << std::endl;
    }
    
    std::vector<sometype> newItem = {32, 33};
    par.emplace_back(newItem);
    
}

class VectorAccessor {
    std::vector<std::vector<sometype>>& m_vec;
public:
	VectorAccessor(std::vector<std::vector<sometype>>& v) : m_vec(v) {}

	template<typename V>
	void addVector(V&& vec) {
		static_assert(std::is_same<typename std::remove_reference<V>::type, 
			std::vector<sometype>>::value, "Not the right type");
		m_vec.emplace_back(std::forward<V>(vec));
	}
    
    std::vector<sometype> accessVector(size_t index) {
        return m_vec[index];
    }
};

int main(int argc, char ** argv)
{

    std::vector<std::vector<sometype>> vec;
	VectorAccessor vAcc(vec);


	// Add an element through the vector accessor
	std::vector<sometype> firstVector = {42};
    firstVector.emplace_back(52);
	vAcc.addVector(firstVector);
    
    // Call bar and add a few elements
    bar(vec);
    
    // Now access stuff with the usual wrapper
    std::cout << "Elements added by bar:" << std::endl;
    std::cout << "Subvector: {";
    for (auto& sometypeItem : vAcc.accessVector(1)) {
        std::cout << sometypeItem.value << " ";
    }
    std::cout << "};" << std::endl;

    return 0;
}