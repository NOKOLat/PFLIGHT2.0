#include "../state_headers.hpp"


StateError InitState::init(StateContext& context) {

    return StateError::NONE;
}


StateError InitState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult InitState::evaluateNextState(StateContext& context) {

    return {StateChange::STATE_CHANGE, StateID::CALIBRATION};
}


StateID InitState::getStateID() const {

    return StateID::INIT;
}
