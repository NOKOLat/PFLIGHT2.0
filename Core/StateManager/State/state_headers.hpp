#ifndef STATE_HEADERS_HPP
#define STATE_HEADERS_HPP

#include "../StateInterface/state_interface.hpp"
#include "../common/state_utility.hpp"
#include "../common/state_context.hpp"


// --- Init ---

class InitState : public StateInterface {

    public:
        virtual ~InitState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};

class CalibrationState : public StateInterface {

    public:
        virtual ~CalibrationState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


// --- PreArm ---

class PreArmState : public StateInterface {

    public:
        virtual ~PreArmState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};

class ArmState : public StateInterface {

    public:
        virtual ~ArmState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};

class PreFlightState : public StateInterface {

    public:
        virtual ~PreFlightState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


// --- Flight ---

class FlightStateBase : public StateInterface {

    public:
        virtual ~FlightStateBase() = default;
        StateError  init(StateContext& context) final;
        StateResult update(StateContext& context) final;

    protected:
        virtual StateError  onInit(StateContext& context)   = 0;
        virtual StateResult onUpdate(StateContext& context) = 0;
};

class FlightState : public FlightStateBase {

    public:
        virtual ~FlightState() = default;
        StateID     getStateID() const override;

    protected:
        StateError  onInit(StateContext& context) override;
        StateResult onUpdate(StateContext& context) override;
};

class AutoFlightState : public FlightStateBase {

    public:
        virtual ~AutoFlightState() = default;
        StateID     getStateID() const override;

    protected:
        StateError  onInit(StateContext& context) override;
        StateResult onUpdate(StateContext& context) override;
};


// --- PostFlight ---

class DisArmState : public StateInterface {

    public:
        virtual ~DisArmState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


// --- Error ---

class ErrorState : public StateInterface {

    public:
        virtual ~ErrorState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};

// EMERGENCY_STOP: StateManager フォールバック専用
class EmergencyStopState : public StateInterface {

    public:
        virtual ~EmergencyStopState() = default;
        StateError  init(StateContext& context) override;
        StateResult update(StateContext& context) override;
        StateID     getStateID() const override;
};


#endif // STATE_HEADERS_HPP
