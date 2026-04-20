#include "../state_headers.hpp"


StateError FlightState::onInit(StateContext& context) {

    return StateError::NONE;
}


StateError FlightState::onUpdate(StateContext& context) {

    return StateError::NONE;
}


StateResult FlightState::onEvaluateNextState(StateContext& context) {

    // Armスイッチが無効になったらDisArmStateへ遷移
    if(context.sbus_data.arm == SwitchPosition::LOW){

        return {StateChange::STATE_CHANGE, StateID::DIS_ARM};
    }

    // Auto Missionスイッチが有効になったらAutoFlightStateへ遷移
    if(context.sbus_data.auto_mission == SwitchPosition::HIGH){

        return {StateChange::STATE_CHANGE, StateID::AUTO_FLIGHT};
    }

    return {StateChange::NO_STATE_CHANGE, StateID::FLIGHT};
}


StateID FlightState::getStateID() const {

    return StateID::FLIGHT;
}
