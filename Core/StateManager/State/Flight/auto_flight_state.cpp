#include "../state_headers.hpp"


StateError AutoFlightState::onInit(StateContext& context) {

    return StateError::NONE;
}


StateResult AutoFlightState::onUpdate(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::AUTO_FLIGHT, StateError::NONE};
}


StateID AutoFlightState::getStateID() const {

    return StateID::AUTO_FLIGHT;
}
