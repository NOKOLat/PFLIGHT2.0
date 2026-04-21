#include "../state_headers.hpp"
#include <cmath>


StateError FlightStateBase::init(StateContext& context) {

    return onInit(context);
}


StateError FlightStateBase::update(StateContext& context) {

    // センサーデータを取得（加速度: m/s², ジャイロ: dps）
    context.imu->GetData(context.accel_data.data(), context.gyro_data.data());

    printf("Accel: [%.2f, %.2f, %.2f] m/s², Gyro: [%.2f, %.2f, %.2f] dps\n",
            context.accel_data[0], context.accel_data[1], context.accel_data[2],
            context.gyro_data[0], context.gyro_data[1], context.gyro_data[2]);

    // ジャイロを dps → rad/s に変換
    constexpr float DEG_TO_RAD = static_cast<float>(M_PI) / 180.0f;
    float gyro_rad[3] = {
        context.gyro_data[0] * DEG_TO_RAD,
        context.gyro_data[1] * DEG_TO_RAD,
        context.gyro_data[2] * DEG_TO_RAD,
    };

    // EKF 更新（加速度は内部で正規化される）
    AttitudeEKF_Update(&context.ekf.value(), context.accel_data.data(), gyro_rad);

    // 推定角度を context に格納（単位: rad）
    context.angle.roll  = AttitudeEKF_GetRoll(&context.ekf.value());
    context.angle.pitch = AttitudeEKF_GetPitch(&context.ekf.value());
    context.angle.yaw   = AttitudeEKF_GetYaw(&context.ekf.value());

    printf("Roll: %.2f deg, Pitch: %.2f deg, Yaw: %.2f deg\n",
           context.angle.roll * 180.0f / static_cast<float>(M_PI),
           context.angle.pitch * 180.0f / static_cast<float>(M_PI),
           context.angle.yaw * 180.0f / static_cast<float>(M_PI));

    return onUpdate(context);
}


StateResult FlightStateBase::evaluateNextState(StateContext& context) {

    return onEvaluateNextState(context);
}
