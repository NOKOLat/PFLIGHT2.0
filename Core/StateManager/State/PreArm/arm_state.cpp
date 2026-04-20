#include "../state_headers.hpp"


StateError ArmState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult ArmState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::ARM, StateError::NONE};
}


StateID ArmState::getStateID() const {

    return StateID::ARM;
}
