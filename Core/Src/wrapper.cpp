#include "wrapper.hpp"
#include "StateManager/state_manager.hpp"
#include "usart.h"

StateManager state_manager(StateID::INIT);

void init(){

	state_manager.init();
}

void loop(){

	state_manager.update();
	HAL_Delay(100);
}
