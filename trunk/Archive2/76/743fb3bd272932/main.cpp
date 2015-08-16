#include <stack>
#include <iostream>

class StateManager;
class State {
    public:
        State(StateManager* m) {
            this->m_manager = m;
        };
    private:
        StateManager* m_manager;
};

class StateA : public State {
    using State::State;
};
class StateB : public State {
    using State::State;
};

class StateManager {
    public:
        template<typename T>
        void addState() {
            // how would we know that T is of type State now and its constructor takes a StateManager reference?
            this->m_states.push(new T(this));
        }
        void printStates() {
            std::cout << this->m_states.size() << "\n";
        }
    private:
        std::stack<State*> m_states;
};

int main() {
    StateManager sm;
    sm.addState<StateA>();
    sm.addState<StateB>();
    sm.printStates();
    return 0;
}
