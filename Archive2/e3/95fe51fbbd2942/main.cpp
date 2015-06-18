#include <iostream>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace {

    using namespace boost::msm;
    using namespace boost::msm::front;
    namespace mpl = boost::mpl;

    struct EvGotoSub1 {};
    struct EvGotoSub2 {}; struct EvGotoSub1FromSub2{};

    struct MainSM_;
    using Main = back::state_machine<MainSM_>;    
    struct Sub1SM_;
    using Sub1 = back::state_machine<Sub1SM_>;
    struct Sub2SM_;
    using Sub2 = back::state_machine<Sub2SM_>;

    struct Sub1SM_ : state_machine_def<Sub1SM_> {
        struct Started : state<> { template <class Event, class Fsm>  void on_entry(Event const&, Fsm& ) {std::cout <<"entering: Sub1" << std::endl;}  };
        using initial_state = mpl::vector<Started>;
        struct transition_table:mpl::vector<
        Row<Started, EvGotoSub2, Sub2, none, none>
        > {};
    };

    struct Sub1a : state_machine_def<Sub1a> {  struct Started : state<> { template <class Event, class Fsm>  void on_entry(Event const&, Fsm& ) {std::cout <<"entering: Sub1a" << std::endl;}  };
        using initial_state = mpl::vector<Started>;
        
         struct transition_table:mpl::vector<
        // Uncomment line below to break things
        //Row<Started, EvGotoSub1FromSub2, Sub1a, none, none>
        > {};
        
        };

    struct Sub2SM_ : state_machine_def<Sub2SM_> {
        struct Started : state<> { template <class Event, class Fsm>  void on_entry(Event const&, Fsm& ) {std::cout <<"entering: Sub2" << std::endl;}   };
        using initial_state = mpl::vector<Started>;
        struct transition_table:mpl::vector<
        // Uncomment line below to break things
        Row<Started, EvGotoSub1FromSub2, Sub1a, none, none>
        > {};
    };

    struct MainSM_ : state_machine_def<MainSM_> {
        struct Started : state<> { };
        using initial_state = mpl::vector<Started>;
        struct transition_table:mpl::vector<
          Row<Started, EvGotoSub1, Sub1, none, none>,
          Row<Started, EvGotoSub2, Sub2, none, none>
        > {};
    };
}

int main() {

    Main main;
    main.start();
    main.process_event(EvGotoSub1());
    main.process_event(EvGotoSub2());
    main.process_event(EvGotoSub1FromSub2());
}