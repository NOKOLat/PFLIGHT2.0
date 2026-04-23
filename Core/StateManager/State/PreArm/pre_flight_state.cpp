#include "../state_headers.hpp"


StateError PreFlightState::init(StateContext& context) {

    return StateError::NONE;
}


StateError PreFlightState::update(StateContext& context) {

	// サーボを動かす（スロットルは0%, サーボの最大角は40度）
    context.pwm_manager->setServoDirect(0, context.sbus_data.pitch * 0.4);
    context.pwm_manager->setServoDirect(1, context.sbus_data.pitch * 0.4);

    return StateError::NONE;
}


StateResult PreFlightState::evaluateNextState(StateContext& context) {

	if(context.sbus_data.arm !=  SwitchPosition::HIGH){

		return {StateChange::STATE_CHANGE, StateID::PRE_ARM};
	}

    // Safetyスイッチが有効になったらFlightStateへ遷移
    if(context.sbus_data.safety == SwitchPosition::HIGH){

        return {StateChange::STATE_CHANGE, StateID::FLIGHT};
    }

    return {StateChange::NO_STATE_CHANGE, StateID::PRE_FLIGHT};
}


StateID PreFlightState::getStateID() const {

    return StateID::PRE_FLIGHT;
}
