#include "../state_headers.hpp"


StateError PreFlightState::init(StateContext& context) {

    return StateError::NONE;
}


StateError PreFlightState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult PreFlightState::evaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::PRE_FLIGHT};
}


StateID PreFlightState::getStateID() const {

    return StateID::PRE_FLIGHT;
}
