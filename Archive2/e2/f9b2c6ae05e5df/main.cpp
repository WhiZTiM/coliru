#include <vector>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

class State_Idle{};
class State_WaitingToTurnOn{};
class State_WaitingToTurnOff{};

typedef boost::mpl::vector <
    State_Idle,
    State_WaitingToTurnOn,
    State_WaitingToTurnOff
> ::type StateListX;


template <class StateList>class MosStateMachine;
typedef std::vector<void *> StateTable;


template <class StateList>
class MosStateMachine
{
public:
    explicit MosStateMachine(){}
    ~MosStateMachine(){}
    template <class State> void PerformStateTransition(){}

    struct detail
    {
        typedef std::vector<void (MosStateMachine::*)()> StateTable;
        static const int NumberOfStates = boost::mpl::size<StateList>::value;

        
        struct TableFiller
        {
            TableFiller(StateTable& state_table):table(state_table){}
            StateTable& table;
            
            template <class Index>
            void operator()(Index idx) const
            {
                table.at(idx) = &MosStateMachine::template PerformStateTransition <
                    typename boost::mpl::at<StateList,Index>::type > ;
            }
        };


        static StateTable GenerateTable()
        {
            StateTable table(NumberOfStates);
            boost::mpl::for_each<boost::mpl::range_c<int,0,NumberOfStates> >(TableFiller(table));
            return table;
        }
    };


    void PerformStateTransitionById(int stateId)
    {

        static typename detail::StateTable lookupTable = detail::GenerateTable();


        (this->*(lookupTable.at(stateId)))();
    }
};

int main(int argc, char* argv[])
{
    MosStateMachine<StateListX>();
    return 0;
}
