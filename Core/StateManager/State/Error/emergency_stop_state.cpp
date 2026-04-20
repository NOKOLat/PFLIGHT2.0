#include "../state_headers.hpp"

StateError EmergencyStopState::init(StateContext& context) {

    return StateError::NONE;
}

StateError EmergencyStopState::update(StateContext& context) {

    return StateError::CRITICAL_STOPPED;
}


StateResult EmergencyStopState::evaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::EMERGENCY_STOP};
}


StateID EmergencyStopState::getStateID() const {
    
    return StateID::EMERGENCY_STOP;
}
