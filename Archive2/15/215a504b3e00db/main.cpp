#include <string>
#include <iostream>
#include <cstring>
#include <typeinfo>

using namespace std;
class Var
{
    class Data;
	class NData;
	class SData;

	Var(Data* _pdata) : pdata(_pdata){}
	mutable const char* mytype = NULL;
	const char* calc_type()const{
		mytype = typeid(*pdata).name();
		return mytype;
	}

public:
	Var(int i) :pdata(new NData(i)){}
	Var(const char* s) :pdata(new SData(s)){}
	Var(const Var& other);
	~Var(){ delete pdata; }
	Var& operator=(const Var& other);
	Var operator+(const Var& var)const{
		return pdata->add(var.pdata);
	}
	const char* type()const{
		return mytype != NULL ? mytype : calc_type();
	}

	friend ostream& operator<<(ostream& out, const Var& v){
		return out << v.pdata->toString() << " (" << v.type()
			<< "@" << (void*)v.pdata << ") ";
	}

private:
	class Data{
		const char* str;
	protected:
		Data(const char* s) :str(new char[strlen(s) + 1]){
			strcpy((char*)str, s);
		}

	public:
		const char* toString()const{ return str; }
		virtual ~Data(){ delete[]str; }
		virtual Data* clone()const = 0;
		virtual Data* add(const Data* other)const = 0;
		virtual Data* add2(const NData* other)const = 0;
		virtual Data* add2(const SData* other)const = 0;
		static Data* add(const NData*, const NData*);
		static Data* add(const Data*, const Data*);
	};

	class NData :public Data{
		int i;
	public:
		NData(int _i) :Data(std::to_string(_i).c_str()), i(_i){}
		Data* clone()const { return new NData(i); }
		Data* add(const Data* o)const{ return o->add2(this); }
		Data* add2(const NData* o)const{ return Data::add(o, this); }
		Data* add2(const SData* o)const{ return Data::add(o, this); }

		static NData* add(const NData* i1, const NData* i2){
			return new NData(i1->i +i2->i);
		}

	};

	class SData :public Data{
	public:
		SData(const char* _str) :Data(string(_str).c_str()){}
		Data* clone() const { return new SData(toString()); }
		Data* add(const Data* o)const{ return o->add2(this); }
		Data* add2(const NData* o)const { return Data::add(o, this); }
		Data* add2(const SData* o)const { return Data::add(o, this); }
		static SData* concat(const Data* s1, const Data* s2){
			string s = s1->toString();
			s += s2->toString();
			return new SData(s.c_str());
		}
	};
	Data* pdata;
};

Var::Data* Var::Data::add(const Var::NData* a,
	const Var::NData* b){
	return NData::add(a, b);
}

Var::Data* Var::Data::add(const Var::Data* a, const Var::Data* b){
	return SData::concat(a, b);
}

Var::Var(const Var& o){ pdata = o.pdata->clone(); }

Var& Var::operator=(const Var& o){
	if (pdata != o.pdata){
		delete pdata;
		pdata = o.pdata->clone();
		//mytype = o.mytype;
	}

	return *this;
}

void printAddTest(const Var* v, int size){
	for (int i = 0; i < size-1; i++)
	{
		cout << v[i] << " +" << v[i + 1] << " = " << (v[i] + v[i + 1]) << endl;
	}
}

int main(){
	Var varArr[] = { 1, "2", "3", 4, 5 };
	printAddTest(varArr, sizeof(varArr) / sizeof(varArr[0]));
	varArr[0] = 1;
	varArr[1] = varArr[1];
	varArr[3] = "4";
	varArr[4] = 5;
	printAddTest(varArr, sizeof(varArr) / sizeof(varArr[0]));
    return 0;
}