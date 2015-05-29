#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(const std::vector<int> &a, const std::vector<int> &b) {
    cout << "COMPARE FUNCTION" << endl;
    cout << "a[0] = " << a[0] << endl;
    cout << "a[1] = " << a[1] << endl;
    cout << "b[0] = " << b[0] << endl;
    cout << "b[1] = " << b[1] << endl;

    bool ret = a < b;

    return ret;
}

int main()
{
    vector<int> vector_int1 = {1, 2};
    vector<int> vector_int2 = {1, 3};

    std::vector<std::vector<int>> vector_of_vectors;

    vector_of_vectors.emplace_back(vector_int1);    
    vector_of_vectors.emplace_back(vector_int2);

    cout << "BEFORE SORTING" << endl;
    cout << "a[0] = " << (vector_of_vectors[0])[0] << endl;
    cout << "a[1] = " << (vector_of_vectors[0])[1] << endl;
    cout << "b[0] = " << (vector_of_vectors[1])[0] << endl;
    cout << "b[1] = " << (vector_of_vectors[1])[1] << endl;

    std::sort(vector_of_vectors.begin(), vector_of_vectors.end(), compare);

    cout << "AFTER SORTING" << endl;
    cout << "a[0] = " << (vector_of_vectors[0])[0] << endl;
    cout << "a[1] = " << (vector_of_vectors[0])[1] << endl;
    cout << "b[0] = " << (vector_of_vectors[1])[0] << endl;
    cout << "b[1] = " << (vector_of_vectors[1])[1] << endl;
}