#include <vector>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>

class State_Idle{};
class State_WaitingToTurnOn{};
class State_WaitingToTurnOff{};

typedef boost::mpl::vector <
    State_Idle,
    State_WaitingToTurnOn,
    State_WaitingToTurnOff
> ::type StateListX;

#ifdef __linux__

template <class StateList>class MosStateMachine;
typedef std::vector<void *> StateTable;

#if 0
// Failed attempt NO.1
// Of course it fails, as there is no partial specialization of function template
template <class StateList, int N>
static void FillTable(StateTable& table)
{
    table.at(N) = (void*)(&MosStateMachine<StateList>::template PerformStateTransition
        <typename boost::mpl::at < StateList, boost::mpl::int_<N> > ::type >);
    FillTable<StateList, N + 1>(table);
}

template <class StateList>
void FillTable <StateList, boost::mpl::size<StateList>::value>(StateTable& table){}
// error: function template partial specialization ‘FillTable<StateList, boost::mpl::size<Sequence>::value>’ is not allowed

template <class StateList>
static StateTable GenerateTable()
{
    StateTable table(boost::mpl::size<StateList>::value);
    FillTable<StateList, 0>(table);
    return table;
}

#endif

#if 1
// Failed attempt NO.2
// Leverage class template partial specialization
// It fails because the "specialized template argument" is dependent on another argument 
// (boost::mpl::size<StateList>::value  to  StateList)
template <class StateList, class Index>  //CHANGED
struct Bar
{
    void operator()(StateTable& table)
    {
        table.at(Index::value) = &MosStateMachine<StateList>::template PerformStateTransition
            < typename boost::mpl::at < StateList, Index > ::type > ;   
        Bar<StateList, boost::mpl::int_<Index::value + 1> > b;   //CHANGED (3 TIMES)
        b(table);
    }
};

// error: template argument ‘boost::mpl::size<Sequence>::value’ involves template parameter(s)
template <class StateList>
struct Bar < StateList, boost::mpl::int_<boost::mpl::size<StateList>::value> >  //CHANGED
{
    void operator()(StateTable& table){}
};

template <class StateList>
static StateTable GenerateTable()
{
    StateTable table(boost::mpl::size<StateList>::value);
    Bar<StateList, boost::mpl::int_<0> > b;  //CHANGED
    b(table);
    return table;
}
#endif

#endif // !__linux__

template <class StateList>
class MosStateMachine
{
public:
    explicit MosStateMachine(){}
    ~MosStateMachine(){}
    template <class State> void PerformStateTransition(){}

#ifndef __linux__
    // Windows version. It works with MSVC. But does not conform to C++ standard and g++. 
    // Specialization should be out of this class. Then I had failed attempts NO.1 and 2 as above. 
    struct detail
    {
        typedef std::vector<void (MosStateMachine::*)()> StateTable;
        static const int NumberOfStates = boost::mpl::size<StateList>::value;

        template <int N>
        static void FillTable(StateTable& table)
        {
            // The following line of code is the very essential that all these is about. 
            // Need to do this over a sequence of compile time integer constant
            table.at(N) = &MosStateMachine::PerformStateTransition <
                typename boost::mpl::at<StateList, boost::mpl::int_<N> >::type > ;
            FillTable<N + 1>(table);
        }

        template <> static void FillTable<detail::NumberOfStates>(StateTable& table){}

        static StateTable GenerateTable()
        {
            StateTable table(NumberOfStates);
            FillTable<0>(table);
            return table;
        }
    };
#endif // !__linux__

    void PerformStateTransitionById(int stateId)
    {
#ifndef __linux__
        static typename std::vector<void (MosStateMachine::*)()> lookupTable = detail::GenerateTable();
#else
        static typename std::vector<void (MosStateMachine::*)()> lookupTable = GenerateTable<StateList>();
#endif // !__linux__

        (this->*(lookupTable.at(stateId)))();
    }
};

int main(int argc, char* argv[])
{
    MosStateMachine<StateListX>();
    return 0;
}
