#include "../state_headers.hpp"


StateError DisArmState::init(StateContext& context) {

    return StateError::NONE;
}


StateError DisArmState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult DisArmState::evaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::DIS_ARM};
}


StateID DisArmState::getStateID() const {

    return StateID::DIS_ARM;
}
