#include "wrapper.hpp"
#include "StateManager/state_manager.hpp"
#include "isr_manager.hpp"
#include "usart.h"

StateManager state_manager(StateID::INIT);

void init(){

	printf("Build: 1\n");
    state_manager.init();
}

void loop(){

    state_manager.update();
    HAL_Delay(100);
}

// UART アイドルライン受信コールバック（ISRManager に委譲）
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {

    ISRManager::handleUartRxEvent(huart, Size);
}
