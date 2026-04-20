#include "../state_headers.hpp"


StateError PreArmState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult PreArmState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::PRE_ARM, StateError::NONE};
}


StateID PreArmState::getStateID() const {

    return StateID::PRE_ARM;
}
