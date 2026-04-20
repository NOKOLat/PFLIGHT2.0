#include "../state_headers.hpp"


StateError StateA::init(StateContext& context) {

    return StateError::NONE;
}


StateResult StateA::update(StateContext& context) {

    return {StateChange::NO_STATE_CHANGE, StateID::STATE_A, StateError::NONE};
}


StateID StateA::getStateID() const {
    
    return StateID::STATE_A;
}
