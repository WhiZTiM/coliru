#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Record {
    int student_id;
    int pin_number;
    std::string first_name;
    std::string last_name;
    std::vector<int> grades;

    static bool by_id_descending(Record const &a, Record const &b) { return a.student_id > b.student_id; }
};

class P4Grades {
  public: // public interfaces for this class
    P4Grades() = default;

    static P4Grades read_from(std::string const &fname);

    bool operator<(P4Grades const &other) const { return table.size() < other.table.size(); }
    bool operator<(size_t n) const { return table.size() < n; }
    void operator+=(P4Grades const g2) { table.insert(table.end(), g2.table.begin(), g2.table.end()); }

    void P4Sort() { std::sort(table.begin(), table.end(), Record::by_id_descending); }

  private:
    typedef std::vector<Record> Table;
    Table table;

    P4Grades(Table&& table) : table(std::move(table)) { }
};

P4Grades P4Grades::read_from(std::string const &fname) {
    std::ifstream input_file(fname);

    Table table;

    std::string line;
    while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        Record newrecord;
        if (input_file >> newrecord.student_id >> newrecord.pin_number >> newrecord.first_name >> newrecord.last_name) {
            int grade;
            while (input_file >> grade)
                newrecord.grades.push_back(grade);

            table.push_back(newrecord);

            // assert(newrecord.grades.size() == number_of_projects);
        } else {
            throw std::runtime_error("Parse error\n");
        }
    }
    // assert(table.size() == number_of_students);
    return P4Grades(std::move(table));
}

int main() {
    // declare the output file
    std::ofstream output_file("out.4");

    // no clue what else should be done...
}
