#include "../state_headers.hpp"


StateError InitState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult InitState::update(StateContext& context) {

    return {StateChange::STATE_CHANGE, StateID::CALIBRATION, StateError::NONE};
}


StateID InitState::getStateID() const {

    return StateID::INIT;
}
