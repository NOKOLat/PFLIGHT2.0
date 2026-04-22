#include "../state_headers.hpp"


StateError ErrorState::init(StateContext& context) {

    // エラー発生時: モーターを停止する
    if (context.pwm_manager) {

        context.pwm_manager->stop();
    }

    return StateError::NONE;
}


StateError ErrorState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult ErrorState::evaluateNextState(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::ERROR};
}


StateID ErrorState::getStateID() const {

    return StateID::ERROR;
}
