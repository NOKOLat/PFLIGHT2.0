#include "../state_headers.hpp"


StateError FlightState::onInit(StateContext& context) {

    return StateError::NONE;
}


StateError FlightState::onUpdate(StateContext& context) {

    return StateError::NONE;
}


StateResult FlightState::onEvaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::FLIGHT};
}


StateID FlightState::getStateID() const {

    return StateID::FLIGHT;
}
