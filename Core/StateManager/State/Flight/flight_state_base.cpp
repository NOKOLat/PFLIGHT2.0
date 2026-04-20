#include "../state_headers.hpp"


StateError FlightStateBase::init(StateContext& context) {

    return onInit(context);
}


StateError FlightStateBase::update(StateContext& context) {

    return onUpdate(context);
}


StateResult FlightStateBase::evaluateNextState(StateContext& context) {

    return onEvaluateNextState(context);
}
