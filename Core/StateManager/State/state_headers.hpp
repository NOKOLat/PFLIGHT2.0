#ifndef STATE_HEADERS_HPP
#define STATE_HEADERS_HPP

#include "../StateInterface/state_interface.hpp"
#include "../common/state_utility.hpp"
#include "../common/state_context.hpp"


class IdleState : public StateInterface {
    
    public:
        virtual ~IdleState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;

};


// STATE_A
class StateA : public StateInterface {

    public:
        virtual ~StateA() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


// STATE_B
class StateB : public StateInterface {

    public:
        virtual ~StateB() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};



// HARDWARE_ERROR
class HardwareErrorState : public StateInterface {

    public:
        virtual ~HardwareErrorState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


// EMERGENCY_STOP
class EmergencyStopState : public StateInterface {

    public:
        virtual ~EmergencyStopState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


#endif // STATE_HEADERS_HPP
