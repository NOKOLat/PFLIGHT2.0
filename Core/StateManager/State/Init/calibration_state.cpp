#include "../state_headers.hpp"


StateError CalibrationState::init(StateContext& context) {

    return StateError::NONE;
}


StateError CalibrationState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult CalibrationState::evaluateNextState(StateContext& context) {



    return {StateChange::STATE_CHANGE, StateID::PRE_ARM};
}


StateID CalibrationState::getStateID() const {

    return StateID::CALIBRATION;
}
