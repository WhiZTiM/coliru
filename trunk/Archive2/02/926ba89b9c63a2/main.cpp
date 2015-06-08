#include <vector>
#include <iostream>

struct Employee {
    int getID() const { return _id; }

  private:
    int _id = generate_id();

    static int generate_id() {
        static int next = 0;
        return ++next;
    }
};
struct DeveloperEmployee : Employee {
    DeveloperEmployee(std::string const& descr, std::string const& project)
        : _description(descr), _project(project) { }

  private:
    std::string _description;
    std::string _project;

    friend std::ostream& operator<<(std::ostream& os, DeveloperEmployee const& de) {
        return os << "id:" << de.getID() << " descr:'" << de._description << "' project:'" << de._project << "'"; 
    }
};

class Company {
  private:
    std::vector<Employee> _table;
    std::string _des;

  public:
    Company &operator+=(const Employee &emp) {
        _table.push_back(emp);
        return *this;
    }
    void setDescription(std::string des) { _des = des; }
};


int main() {
    Company company;
    DeveloperEmployee a("description", "project");

    // int id = a.getID();
    std::cout << a << std::endl; // Developer ID = 2, project = hw5

    company += a;
}
