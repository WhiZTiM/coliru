#include <iostream>
#include <map>
#include <set>
#include "boost/any.hpp"

struct Creature
{
    std::string name = "Nemo";
	Creature(std::string name): name(std::move(name)) {}
};

namespace Event
{
enum EVENT_TYPE { CRY, DIE };

struct EventCry {
    std::string text;
    Creature* origin;
};

struct EventDie {
    Creature* dead;
};

struct Event {
    EVENT_TYPE type;
    boost::any data;
};

struct EventHandler {
    virtual void handle_event(const Event& event) = 0;
};


namespace detail
{
class EventDispatcher
{
  public:
    bool add_listener(EVENT_TYPE event, EventHandler* handler)
    {
        return listeners[event].insert(handler).second;
    }

    bool remove_listener(EVENT_TYPE event, EventHandler* handler)
    {
        return listeners[event].erase(handler);
    }

    void raise_event(const Event& event)
    {
        for(auto&& el: listeners[event.type])
            el->handle_event(event);
    }

    static EventDispatcher& instance()
    {
        static EventDispatcher d;
        return d;
    }
  private:
    std::map<EVENT_TYPE, std::set<EventHandler*>> listeners;
};
}

bool add_event_listener(EVENT_TYPE event, EventHandler* handler)
{
    return detail::EventDispatcher::instance().add_listener(event, handler);
}

bool remove_event_listener(EVENT_TYPE event, EventHandler* handler)
{
    return detail::EventDispatcher::instance().remove_listener(event, handler);
}

void raise_event(const Event& event)
{
    detail::EventDispatcher::instance().raise_event(event);
}

}

struct sample_creature : Creature
{
	sample_creature(std::string name) : Creature(std::move(name)) {}
	~sample_creature()
	{
		Event::raise_event({Event::DIE, Event::EventDie{this}});
		std::cout << this << " died\n";
	};
};

struct cat: sample_creature
{
	cat() : sample_creature("Cat") {}
	void meow()
	{
		Event::raise_event({Event::CRY, Event::EventCry{"meow", this}});
	}
};

struct simple_listener : Event::EventHandler
{
	virtual void handle_event(const Event::Event& event) override
	{
		switch(event.type)
		{
			case Event::CRY: {
				const Event::EventCry& e = boost::any_cast<const Event::EventCry&>(event.data);
				std::cout << e.origin->name << " says " << e.text << '\n';
				break;
			}
			case Event::DIE: {
				const Event::EventDie& e = boost::any_cast<const Event::EventDie&>(event.data);
				std::cout << "Creature " << e.dead << " died\n";
				break;
			}
		}
	}
};


int main()
{
	simple_listener foo;
	add_event_listener(Event::CRY, &foo);
	add_event_listener(Event::DIE, &foo);
	{
		cat greebo;
		{
			cat kitty;
			kitty.meow();
		}
		remove_event_listener(Event::DIE, &foo);
		//You won't see event handling message for Greebo's death, only destructor message.
	}
}
