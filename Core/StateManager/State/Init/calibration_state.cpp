#include "../state_headers.hpp"


StateError CalibrationState::init(StateContext& context) {

    return StateError::NONE;
}


StateResult CalibrationState::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::CALIBRATION, StateError::NONE};
}


StateID CalibrationState::getStateID() const {

    return StateID::CALIBRATION;
}
