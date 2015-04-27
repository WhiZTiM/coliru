#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

class Attendance    	//parent class called Attendance
{
  public:
     Attendance() : name("Not Assigned"), id(0), num_modules(0),num_contact_hours(0), num_attended(0) { }		//default constructor
     //below is a constructor 
     Attendance(string n, string id, int num_mod, int num_hours, int num_att) : name(n), id(id), num_modules(num_mod), num_contact_hours(num_hours), num_attended(num_att) { }
      ~Attendance() { }	//destructor

  // you place your other functions here...

  protected:
     string name;		//name of person
     string id;			//staff or studentid
     int num_modules, num_contact_hours, num_attended;	//the array contains the number of hours in the first sem and second sem
};



class Staff : public Attendance		//subclass for Staff attendace
{
public:
   void initialize_staff(string, string, int, int, int, int, int);
   Staff() : lecture_hours(16), type("Full time") { }		//default constructor, default lecturing hours should be 16
   Staff(string n, string id, int mod, int contact, int attend, int hours, string t) : Attendance(n, id, num_modules, num_contact_hours, num_attended), lecture_hours(hours), type(t) { }
   ~Staff() { }		//destructor
   void setLecturingHours(int hours) { lecture_hours = hours; }	//member function (mutator) of subclass that sets lecture hours
   int LecturingHours() { return lecture_hours; }		//accessor function that returns the lecturer hours
   void setType(string t) { type = t; }		//mutator function for 
   string Lecturer_Type() { return type; }	
   void initialize_staff(string,string,int,int,int,string);
   void add();
   void display();
   bool find_free_pos();
   	friend istream& operator >> (istream& in, Staff& staff_);
	friend ostream& operator << (ostream& out, Staff& staff);
private:
	int lecture_hours;
   string type;  // full time or part-time
};

class Student : public Attendance
{
   public:
    Student() : type("Undefined") {}
    Student(string n, string id, int mod, int attend, int hours, string t) : Attendance(n, id, mod, num_contact_hours, attend), type(t) {}
    ~Student() {};
    void initialize_student(string,string,int,int,int,string);
    void add();
    void display();
    friend istream& operator >> (istream& in, Student& student_);
	friend ostream& operator << (ostream& out, Student& student);
	bool find_free_pos();
    
    void setContactHours(int hours) {};
    int getContactHours() {return num_contact_hours;};
    
    
   private:
   	string type;
    // you populate your variables here
};


int main(int argc, char** argv) 
{
	int i=0, choice_task_menu=0, position=0, num_attend=0, num_modules=0, choice_search, num_contact_hours, lecture_hours;		//variables
	string name, id, type;
	
	
	Student *student; //declaring pointer called student that will point to object of class Student
	student = new Student[50];	//object created in dynamic memory
	
	Staff *staff;		//declaring pointer called staff that will point to object of class Staff
	staff = new Staff[50];	//object created in dynamic memory

	
	Staff staf_count;	//variables just to count the number of rows in file and do nothing else
	Student stud_count;	//variables just to count number of rows in file
	
	ifstream fin1, fin2, fin3, fin4;				// input file stream, fin1 declared
	fin1.open("attendance_student.txt", ios::in);		//open a text file named "student_attendance.txt"
	if(fin1.fail())				//if it fails, output the following and exit the programs
	{
	cout << "Error opening file for reading\n";
	exit(1);
	}
	
	int count_student = 0, count_staff = 0;				//initialize count to zero
	while(fin1 >> stud_count) // while true (there are values to read in), exucute the loop again			|{line includes call to overloading operators}|
	{					
		count_student++; 				//post-increment the count each time the 6 variables (a row) are filled
	}
	fin1.close();			//close file
	cout << "the number of rows in the students file: " << count_student << endl;
	
	
	fin2.open("attendance_staff.txt", ios::in);		//open a text file named "staff_attendance.txt"
	if(fin2.fail())				//if it fails, output the following and exit the programs
	{
	cout << "Error opening file for reading\n";
	exit(1);
	}
	
	count_staff = 0;				//initialize count to zero
	while(fin2 >> staf_count) // while true (there are values to read in), exucute the loop again			|{line includes call to overloading operators}|
	{					
		count_staff++; 				//post-increment the count each time the 6 variables (a row) are filled
	}
	fin2.close();			//close file
	cout << "the number of rows in the staff file: " << count_staff << endl;

	fin3.open("attendance_student.txt", ios::in);		//opens file named "phonebook.txt"
	if(fin1.fail())			//if it fails to open file, display the following and exits program
	{
	cout << "Error opening file for reading\n";
	exit(1);
	}
	
	i = 0;				//read the contents in to myphbk now
	while(fin3 >> student[i] && i < count_student)
	{	
	i++;	
	}
	
	for(i=0;i<50;i++)		//displays every student
	student[i].display();
	
	//now it will operate the staff
	
	fin4.open("attendance_staff.txt", ios::in);		//opens file named "phonebook.txt"
	if(fin4.fail())			//if it fails to open file, display the following and exits program
	{
	cout << "Error opening file for reading\n";
	exit(1);
	}
	
	i = 0;				//read the contents in to myphbk now
	while(fin4 >> staff[i] && i < count_staff)
	{	
	i++;	
	}
	
	for(i=0;i<50;i++)		//displays every contact
	staff[i].display();

	
	//overloading operators later 
	
	

	
	int pos = 0;
	for(pos = 0; pos < 50; pos++)			// initializing everything to undefined, and position to free (position is the second parameter sended in)	
	{
		//the sequence goes like this (name,id,num_modules,num_contact_hours,num_attend,type)
		student[pos].initialize_student( "Undefined", "0", 0, 0, 0,"Undefined");	//initialize everything to zero and strings are undefined
		staff[pos].initialize_staff("Undefined", "0",0 ,0,0, "Undefined");
		//void Student::initialise(string name_,string id_, int num_modules_, int num_contact_hours_, int num_attended_, int type_)
		//void Staff::initialise(string name_, string id_, int num_modules_, int lecture_hours_, int num_attended_, string type_)
		//take previous two comments away
		
	}
	
	cout << "Please select option (1. Add a person/2. Search for a person)" << endl;
	cin >> choice_task_menu;	//menu only gives 2 choices (add or search for an individual)
	
	switch(choice_task_menu)
	{
		case(1):	// add a person, now its classified staff or student
			cout << "Please enter the position of the person (1. Staff/ 2. Student)" << endl;
			cin >> position;

			
			
			//if 1, call staff initialize function, if 2, call student initialize function
			if(position == 1)
			{
				for(int i=0;i<100;i++)
				{	
					if(student[i].find_free_pos())
					{
						student[i].add();
					}
				}
			}
			break;
			
			if(position == 2)
			{
				for(int i=0; i<100; i++)
				{
					if(student[i].find_free_pos())
					{
						student[i].add();
					}
				}
			}
		case(2):
			cout << "How do you want to search (1. Name/2. ID)" << endl;
			cin >> choice_search;
	}
	
	return 0;
}

void Student::initialize_student(string name_,string id_, int num_modules_, int num_contact_hours_, int num_attended_, string type_)
{
	//now assign them to private member variables
	name = name_;
	id = id_;
	num_modules = num_modules_;
	num_contact_hours = num_contact_hours_;
	type = type_;
	num_attended = num_attended_;
	
	
	//end of assigning
}

void Staff::initialize_staff(string name_, string id_, int num_modules_, int lecture_hours_, int num_attended_, string type_)
{
	//assigning to private member variables
	name = name_;
	id = id_;
	num_modules = num_modules_;
	type = type_;
	num_attended = num_attended_;
	lecture_hours = lecture_hours_;
	
}

bool Student::find_free_pos()
{
	if (name == "Undefined")
	{
		return true;
	}
}

bool Staff::find_free_pos()
{
	if (name == "Undefined")
	{
		return true;
	}
}

void Student::add()
{
			cout << "Please enter the type of the person (Full time/Part Time)" << endl;
			cin >> type;
			cout << "Please enter name of person you wish to add" << endl;
			cin >> name;
			cout << "Please enter the ID of the person" << endl;
			cin >> id;		//remember that id is type string
			cout << "Please enter number of contact hours" << endl;
			cin >> num_contact_hours;
			cout << "Please enter number of hours that the person attended" << endl;
			cin >> num_attended;
			cout << "Please enter the number of modules that the person has" << endl;
			cin >> num_modules;
}

void Staff::add()
{
			cout << "Please enter the type of the person (Full time/Part Time)" << endl;
			cin >> type;
			cout << "Please enter name of person you wish to add" << endl;
			cin >> name;
			cout << "Please enter the ID of the person" << endl;
			cin >> id;		//remember that id is type string
			cout << "Please enter number of hours that the person attended" << endl;
			cin >> num_attended;
			cout << "Please enter the number of modules that the person has" << endl;
			cin >> num_modules;
			cout << "Please enter lecture hours (if any)" << endl;
			cin >> lecture_hours;
}

void Student::display()
{
	cout << name << " " << type << " " << id << " " << num_contact_hours << " " <<  num_modules << " " << num_attended;
}

void Staff::display()
{
	cout << name << " " << type << " " << id << " " << lecture_hours << " " <<  num_modules << " " << num_attended;
}

istream& operator >> (istream& in , Staff& staff)		//overloading operator on insertion operator
{
	in >> staff.name >> staff.type >> staff.id >> staff.lecture_hours >> staff.num_modules >> staff.num_attended;
	return in;
}

ostream& operator << (ostream& out , Staff& staff)		//overloading operator on extraction operator
{
	out << staff.name << staff.type << staff.id << staff.lecture_hours << staff.num_modules << staff.num_attended;
	return out;
} 

istream& operator >> (istream& in , Student& student)		//overloading operator on insertion operator
{
	in >> student.name >> student.type >> student.id >> student.num_contact_hours >> student.num_modules >> student.num_attended;
	return in;
}

ostream& operator << (ostream& out , Student& student)		//overloading operator on extraction operator
{
	out << student.name << student.type << student.id << student.num_contact_hours << student.num_modules << student.num_attended;
	return out;
} 