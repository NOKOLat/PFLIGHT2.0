#include "wrapper.hpp"
#include "StateManager/state_manager.hpp"
#include "usart.h"

StateManager state_manager(StateID::IDLE);

void init(){

	state_manager.init();
}

void loop(){

	state_manager.update();
	HAL_Delay(100);
}
