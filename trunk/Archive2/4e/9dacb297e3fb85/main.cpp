#include <iostream>

class Student {
private:
    std::string firstName;
    double grade;
public:
    Student(const std::string &firstName, double grade);

    double getGrade() const;

    friend Student operator+(double grade, const Student &student);

    Student operator+(double grade) const;
}; 

Student::Student(const std::string &firstName, double grade) {
    this->firstName = firstName;
    this->grade = grade;
}

double Student::getGrade() const {
    return grade;
}

Student operator+(double grade, const Student &student) {
    return Student(student.firstName, student.grade + grade);
}

Student Student::operator+(double grade) const {
    return ::operator+(grade, *this);
}

int main() {
    
    return 0;
}