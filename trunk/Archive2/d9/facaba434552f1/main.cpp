#include <iostream>
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

template <class T>
std::string demangle()
{
    const char* name = typeid(T).name();
    int status = -1; 
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status==0) ? res.get() : name ;
}


#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/back/metafunctions.hpp>
#include <boost/mpl/assert.hpp>

using namespace boost::msm;
using namespace boost::msm::front;



template <typename State>
struct BaseState : public boost::msm::front::state<>
{
    template <class Event,class FSM> void on_entry(Event const&,FSM& ) {std::cout << "on_entry: " << demangle<State>()  << std::endl;}
    template <class Event,class FSM> void on_exit(Event const&,FSM& )  {std::cout << "on_exit: " << demangle<State>() << std::endl;}

};


// EVENTS
struct EnterOrthogonal {};

struct Orthogonal1Finished{};
struct Orthogonal2Finished{};
struct Orthogonal3Finished{};



struct SubSM_ : state_machine_def<SubSM_>
{
    struct Started : BaseState<Started>{};
    struct Exit : exit_pseudo_state<none> {};

    struct Orthogonal1 : BaseState<Orthogonal1>{};
    struct Orthogonal2 : BaseState<Orthogonal2>{};
    struct Orthogonal3 : BaseState<Orthogonal3>{};
    
    struct Join : BaseState<Join>{};
            
    typedef boost::mpl::vector<Orthogonal1, Orthogonal2, Orthogonal3> initial_state;
    struct transition_table : boost::mpl::vector<
     Row<Orthogonal1, Orthogonal1Finished, Join, none, none>,
     Row<Orthogonal2, Orthogonal2Finished, Join, none, none>,
     Row<Orthogonal3, Orthogonal3Finished, Join, none, none>
     > {};
};


template <typename SM, typename JoinState = typename SM::Join, typename ExitState = typename SM::Exit>
struct JoinSM  : SM
{
    struct AllJoined{};
    constexpr static int num_regions = boost::mpl::size<typename SM::initial_state>::value;
    int count;
    
    struct Waiting : BaseState<Waiting> {template <class Event,class FSM> void on_entry(const Event& e,FSM& f) { f.count++; if(f.count == FSM::num_regions) { f.process_event(AllJoined()); } BaseState<Waiting>::on_entry(e,f);} };
    
    typedef boost::mpl::vector<
         Row<JoinState, none, Waiting, none, none>,
         Row<Waiting, AllJoined, ExitState, none, none>
    > additional_transition_table;
    
    typedef boost::mpl::joint_view<
      typename SM::transition_table,
      additional_transition_table
    > transition_table;
};


using Sub = back::state_machine<JoinSM<SubSM_>>;

struct MainSM_ : state_machine_def<MainSM_>
{
    struct Started : BaseState<Started>{};
    struct AfterJoin : BaseState<AfterJoin>{};
    using initial_state = boost::mpl::vector<Started>;
    struct transition_table : boost::mpl::vector<
    Row<Started, EnterOrthogonal, Sub, none, none>,
    Row<Sub::exit_pt<SubSM_::Exit>, none, AfterJoin, none, none>
    > {};
};

struct MainSM_;
using Main = back::state_machine<MainSM_>;    



int main()
{

    Main main;
    main.start();
    main.process_event(EnterOrthogonal());
    main.process_event(Orthogonal3Finished());
    main.process_event(Orthogonal1Finished());
    main.process_event(Orthogonal2Finished());
}