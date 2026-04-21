#include "../state_headers.hpp"


StateError FlightStateBase::init(StateContext& context) {

    return onInit(context);
}


StateError FlightStateBase::update(StateContext& context) {

    // センサーデータを取得
    context.imu->GetData(context.accel_data.data(), context.gyro_data.data()); 
}


StateResult FlightStateBase::evaluateNextState(StateContext& context) {

    return onEvaluateNextState(context);
}
