#include "../state_headers.hpp"

StateError IdleState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult IdleState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::IDLE, StateError::NONE};
}


StateID IdleState::getStateID() const {
    return StateID::IDLE;
}
