#include "../state_headers.hpp"


StateError AutoFlightState::onInit(StateContext& context) {

    return StateError::NONE;
}


StateError AutoFlightState::onUpdate(StateContext& context) {

    return StateError::NONE;
}


StateResult AutoFlightState::onEvaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::AUTO_FLIGHT};
}


StateID AutoFlightState::getStateID() const {

    return StateID::AUTO_FLIGHT;
}
