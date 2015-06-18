#include <iostream>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace {

    using namespace boost::msm;
    using namespace boost::msm::front;
    namespace mpl = boost::mpl;

    struct EvGotoSub1 { EvGotoSub1(int d1):d1(d1){} int d1;};
    struct EvGotoSub2 { EvGotoSub2(int d2):d2(d2){} int d2;};

    struct MainSM_;
    using Main = back::state_machine<MainSM_>;    
    struct Sub1SM_;
    using Sub1 = back::state_machine<Sub1SM_>;
    struct Sub2SM_;
    using Sub2 = back::state_machine<Sub2SM_>;

    struct Sub1SM_ : state_machine_def<Sub1SM_> {
        struct Started : state<> {  template <class Event,class Fsm> void on_entry(const Event& e, Fsm&) const { std::cout << "SUB2SM_ Started::on_entry(): d1="<<e.d1 << std::endl; } };
        struct Exit : exit_pseudo_state<EvGotoSub2> {};
        using initial_state = mpl::vector<Started>;
        struct transition_table:mpl::vector<
         Row<Started, EvGotoSub2, Exit, none, none>
        > {};
    };

    struct Sub2SM_ : state_machine_def<Sub2SM_> {
        struct Started : state<> {  template <class Event,class Fsm> void on_entry(const Event& e, Fsm&) const { std::cout << "SUB2SM_ Started::on_entry(): d2="<<e.d2 << std::endl; } };
        struct Exit : exit_pseudo_state<EvGotoSub1> {};
        using initial_state = mpl::vector<Started>;
        struct transition_table:mpl::vector<
        Row<Started, EvGotoSub1, Exit, none, none>
        > {};
    };

    struct MainSM_ : state_machine_def<MainSM_> {
        struct Started : state<> { };
        using initial_state = mpl::vector<Started>;
        struct transition_table:mpl::vector<
        Row<Started, EvGotoSub1, Sub1, none, none>,
        Row<Started, EvGotoSub2, Sub2, none, none>,
        Row<Sub2::exit_pt<Sub2SM_::Exit>, EvGotoSub1, Sub1, none, none>,
        Row<Sub1::exit_pt<Sub1SM_::Exit>, EvGotoSub2, Sub2, none, none>
        > {};
    };
}


int main() {

    Main main;
    main.start();
    main.process_event(EvGotoSub1(0));
    main.process_event(EvGotoSub2(1));
    main.process_event(EvGotoSub1(2));
}