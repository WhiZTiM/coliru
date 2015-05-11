#include <iostream>
#include <memory>
#include <map>

using namespace std;

class Event {
public:
    Event (double time) : _time(time) {}
    double getTime () const { return _time; }
private:
    Event (Event const & e);
    void operator= (Event const &e);
    double _time;
};

class Calendar {
public:
    void addEvent (std::unique_ptr<Event> e) {
        double t = e->getTime(); // get time before trying the next line
        _events.insert(move(make_pair (t, move(e)))); // insert into multimap
    }
private:
    multimap <double, unique_ptr<Event>> _events;
};

int main () {
    unique_ptr<Event> e (new Event(1.0));

    Calendar c;
    c.addEvent (move(e));
}
