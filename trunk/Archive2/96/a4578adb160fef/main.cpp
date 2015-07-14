#include <string>
#include <vector>

// (you say this exists; we can but trust you on that)
class User
{
public:
    bool operator==(const User& other) const { return true; }
};

static const size_t SIZE = 42;

class Room
{

  private:
    std::string room_name;
    User* admin;
  public:
    Room(std::string name, User* admin, User* playersA[SIZE]);
    ~Room();
    bool operator==(const Room& other)const ;
    bool operator==(const Room* other) const;

 };

bool Room :: operator==( const Room& other) const 
{
  bool a = (*(this->admin) == *(other.admin));
  return (a  );
}

int main()
{
    std::vector<Room> r;
}