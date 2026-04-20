#include "../state_headers.hpp"

StateError EmergencyStopState::init(StateContext& context) {

    return StateError::NONE;
}

StateResult EmergencyStopState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::EMERGENCY_STOP, StateError::CRITICAL_STOPPED};
}


StateID EmergencyStopState::getStateID() const {
    
    return StateID::EMERGENCY_STOP;
}
