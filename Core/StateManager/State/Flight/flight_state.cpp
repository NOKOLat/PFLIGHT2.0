#include "../state_headers.hpp"


StateError FlightState::onInit(StateContext& context) {

    if (!context.cascade_pid_manager) {

        return StateError::UPDATE_FAILED_CRITICAL;
    }

    return StateError::NONE;
}


StateError FlightState::onUpdate(StateContext& context) {

    if (!context.cascade_pid_manager) {

        context.pid_output.fill(0.0f);
        return StateError::UPDATE_FAILED_CRITICAL;
    }

    constexpr float RAD_TO_DEG = 180.0f / 3.14159265f;
    constexpr float MAX_COMMAND_ANGLE_DEG = 30.0f;

    const auto& thresholds = nokolat::SBUSRescaler::default_thresholds;

    const float target_pitch_deg = nokolat::SBUSRescaler::sbusToAngle(
        context.sbus_data.raw_data[static_cast<uint8_t>(nokolat::SBUSChannel::PITCH)],
        thresholds.pitch,
        MAX_COMMAND_ANGLE_DEG);
    const float target_roll_deg = nokolat::SBUSRescaler::sbusToAngle(
        context.sbus_data.raw_data[static_cast<uint8_t>(nokolat::SBUSChannel::ROLL)],
        thresholds.roll,
        MAX_COMMAND_ANGLE_DEG);
    const float target_yaw_deg = nokolat::SBUSRescaler::sbusToAngle(
        context.sbus_data.raw_data[static_cast<uint8_t>(nokolat::SBUSChannel::YAW)],
        thresholds.yaw,
        MAX_COMMAND_ANGLE_DEG);

    const float measured_pitch_deg = context.angle.pitch * RAD_TO_DEG;
    const float measured_roll_deg = context.angle.roll * RAD_TO_DEG;
    const float measured_yaw_deg = context.angle.yaw * RAD_TO_DEG;

    context.cascade_pid_manager->calcCascadePIDAllAxes(
        target_pitch_deg, measured_pitch_deg,
        target_roll_deg, measured_roll_deg,
        target_yaw_deg, measured_yaw_deg,
        context.pid_output.data(),
        context.gyro_data[1],
        context.gyro_data[0],
        context.gyro_data[2]);

    context.cascade_pid_manager->updateCycleCounter();
    context.throttle = context.sbus_data.throttle;

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
