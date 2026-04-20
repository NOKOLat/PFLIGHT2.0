#include "../state_headers.hpp"


StateError FlightStateBase::init(StateContext& context) {

    return onInit(context);
}


StateResult FlightStateBase::update(StateContext& context) {

    return onUpdate(context);
}
