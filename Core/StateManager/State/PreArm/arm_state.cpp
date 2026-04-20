#include "../state_headers.hpp"


StateError ArmState::init(StateContext& context) {

    return StateError::NONE;
}


StateError ArmState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult ArmState::evaluateNextState(StateContext& context) {

    return {StateChange::STATE_CHANGE, StateID::PRE_FLIGHT};
}


StateID ArmState::getStateID() const {

    return StateID::ARM;
}
