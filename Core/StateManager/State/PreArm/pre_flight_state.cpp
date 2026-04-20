#include "../state_headers.hpp"


StateError PreFlightState::init(StateContext& context) {

    return StateError::NONE;
}


StateError PreFlightState::update(StateContext& context) {

	printf("throttle: %f\n", context.sbus_data.throttle);
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
