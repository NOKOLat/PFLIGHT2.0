#include "../state_headers.hpp"


StateError FlightState::onInit(StateContext& context) {

    return StateError::NONE;
}


StateResult FlightState::onUpdate(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::FLIGHT, StateError::NONE};
}


StateID FlightState::getStateID() const {

    return StateID::FLIGHT;
}
