#include "../state_headers.hpp"


StateError ErrorState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult ErrorState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::ERROR, StateError::NONE};
}


StateID ErrorState::getStateID() const {

    return StateID::ERROR;
}
