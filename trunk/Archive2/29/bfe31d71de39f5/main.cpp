#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;

class Var {

// forward declaration
class Data;
class IntData;
class StringData;
// end of forward declaration

    Var(Data* _pdata): pdata (_pdata) {}
	mutable const char* mytype = NULL; // C++11 allows such assignment
	const char* calc_type()const {
		mytype = typeid(*pdata).name();
		return mytype;
	}
public:
	Var(int i): pdata (new IntData(i)) {}
	Var(const char* s): pdata (new StringData(s)) {}
	Var(const string& s): pdata (new StringData(s)) {}
	Var(const Var& other);
	~Var() {delete pdata;}
	Var& operator=(const Var& other);
	Var operator+(const Var& var)const {
		return pdata->add(var.pdata);
	}
	const char* type()const {
		return mytype != NULL ? mytype : calc_type();
	}
	friend ostream& operator<<(ostream& out, const Var& v) {
		return out << v.pdata->toString() << " (" << v.type() << "@" << (void*)v.pdata << ")";
	}

private:

	class Data {
	public:
		virtual Data* clone()const=0;
		virtual ~Data(){}
		virtual Data* add(const Data* other)const=0;
		virtual Data* add2(const IntData* other)const=0;
		virtual Data* add2(const StringData* other)const=0;
		virtual string toString()const=0;
		static Data* add(const IntData*, const IntData*);
		static Data* add(const Data*, const Data*);
	};

	class IntData : public Data {
		int i;
	public:
		IntData(int _i): i(_i) {}
		Data* clone()const {
			return new IntData(i);
		}
		static IntData* add(const IntData* i1, const IntData* i2) {
			return new IntData(i1->i + i2->i);
		}
		Data* add(const Data* other)const {
			return other->add2(this);
		}
		Data* add2(const IntData* other)const {
			return Data::add(other, this);
		}
		Data* add2(const StringData* other)const {
			return Data::add(other, this);
		}
		string toString()const {
			return std::to_string(i); // C++11, converts int to std::string
		}
	};

	class StringData : public Data {
		string str;
	public:
		StringData(const string& s): str(s) {}
		Data* clone()const {
			return new StringData(str);
		}
		static StringData* concat(const Data* s1, const Data* s2) {
			return new StringData(s1->toString() + s2->toString());
		}
		Data* add(const Data* other)const {
			return other->add2(this);
		}
		Data* add2(const IntData* other)const {
			return Data::add(other, this);
		}
		Data* add2(const StringData* other)const {
			return Data::add(other, this);
		}
		string toString()const {
			return str;
		}
	};

	// the data held by Var (we are in the private part of class Var)
	Data* pdata;
};

Var::Data* Var::Data::add(const Var::IntData* a, const Var::IntData* b) {
	// int with int results as int
	return IntData::add(a, b);
}

Var::Data* Var::Data::add(const Var::Data* a, const Var::Data* b) {
	// all other cases requires string concatanation
	return StringData::concat(a, b);
}

Var::Var(const Var& other) {
	pdata = other.pdata->clone();
}

Var& Var::operator=(const Var& other) {
	if(pdata != other.pdata) { 
		delete pdata;
		pdata = other.pdata->clone();
	}
	return *this;
}

void printAddTest(const Var* varArr, int size) {
	for(int i=0; i<size-1; ++i) {
		cout << "varArr[" << i << "] + varArr[" << (i+1) << "] = " << varArr[i] << " + " << varArr[i+1] << " = " << varArr[i] + varArr[i+1] << endl;
	}
}

void printArr(const Var* varArr, int size) {
	for(int i=0; i<size; ++i) {
		cout << "varArr[" << i << "] = " << varArr[i] << endl;
	}
}

int main() {

	Var varArr[] = {1, "2", "3", 4, 5};

	printArr(varArr, sizeof(varArr)/sizeof(varArr[0]));
	cout << endl;
	printAddTest(varArr, sizeof(varArr)/sizeof(varArr[0]));

	varArr[0] = varArr[0];
	varArr[1] = 2;
	varArr[2] = 3;
	varArr[3] = "4";

	cout << endl << endl;

	printArr(varArr, sizeof(varArr)/sizeof(varArr[0]));
	cout << endl;
	printAddTest(varArr, sizeof(varArr)/sizeof(varArr[0]));

	return 1;
}