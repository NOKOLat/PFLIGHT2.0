#include "../state_headers.hpp"


StateError ArmState::init(StateContext& context) {

    return StateError::NONE;
}


StateError ArmState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult ArmState::evaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::ARM};
}


StateID ArmState::getStateID() const {

    return StateID::ARM;
}
