#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class node {
public:
    node() : value(0), count(0) {}
    int get_value();
    void set_value(int val);
    unsigned int get_count();
    void inc_count();
    void set_count(unsigned int count);
    
    friend istream& operator>>(istream &in, node &n) {
      in >> n.value;
      n.count = 1;
      return in;
    }
    
    friend ostream& operator<<(ostream &out, const node &n) {
      out << n.value; // What about count?
      return out;
    }
    
    friend bool operator==(const node &lhs, const node &rhs) {
      return lhs.value == rhs.value &&
             lhs.count == rhs.count;
    }
    
    friend bool operator!=(const node &lhs, const node &rhs) {
      return !operator==(lhs, rhs);   
    }
    
    friend bool operator<(const node &lhs, const node &rhs) {
      return tie(lhs.value, lhs.count) < tie(rhs.value, rhs.count);
    }
    
private:
    int value;
    unsigned int count;
};

void printVector(const vector<node> &v);
void fillVector(vector<node>& v);
unsigned count(const vector<node>& v);

int main() {
    vector<node> numbers;
    fillVector(numbers);
    sort(numbers.begin(), numbers.end());
    printVector(numbers);
}

void fillVector(vector<node> &v) {
    ifstream fin;
    fin.open("text.txt");
    if (fin.fail()){
        cout << "text.txt failed to open" << endl;
        exit(0);
    }    
    node temp;
    fin >> temp;
    while (!fin.eof()) {
        v.push_back(temp);
        fin >> temp;
    }
}

void printVector(const vector<node>& v) {
    unsigned temp;
    cout << "N" << "    " << "Count" << endl << endl;
    for (size_t i = 0; i < v.size() - 1; i++) {
        if (v.at(i) == v.at(i + 1)){
            temp += count(v);
        }
        cout << v.at(i) << "    " << temp << endl << endl;
        //i += (temp - 1);
        temp = 1;
    }
    //cout << v.at(v.size() -1) << endl;
}

unsigned count(const vector<node> & v) {
    unsigned temp = 0;
    for (size_t i = 0; i < v.size() - 1; i++){
        if (v.at(i) == v.at(i + 1)){
            temp += 1;
        }
        else {
            break;
        }
    }
    return temp;
}

 