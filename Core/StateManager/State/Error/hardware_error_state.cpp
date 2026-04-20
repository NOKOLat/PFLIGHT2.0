#include "../state_headers.hpp"


StateError HardwareErrorState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult HardwareErrorState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::HARDWARE_ERROR, StateError::NONE};
}


StateID HardwareErrorState::getStateID() const {
    return StateID::HARDWARE_ERROR;
}
