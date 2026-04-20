#ifndef STATE_CONTEXT_HPP
#define STATE_CONTEXT_HPP

#include <cstdint>
#include <functional>
#include <string>
#include "stm32f7xx_hal.h"
#include "SBUS/sbus.h"
#include "sbus_rescaler.hpp"
#include "usart.h"

struct StateContext {

    uint32_t state_change_count = 0;
    std::function<void(const std::string&)> publish_log = [](const std::string&) {};

    // SBUS
    nokolat::SBUS            sbus_receiver;
    UART_HandleTypeDef*      sbus_uart  = &huart5;
    nokolat::RescaledSBUSData sbus_data = {};
};


#endif // STATE_CONTEXT_HPP
