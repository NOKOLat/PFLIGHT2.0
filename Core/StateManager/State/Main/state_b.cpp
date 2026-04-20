#include "../state_headers.hpp"


StateError StateB::init(StateContext& context) {

    return StateError::NONE;
}


StateResult StateB::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::STATE_B, StateError::NONE};
}


StateID StateB::getStateID() const {
    
    return StateID::STATE_B;
}
