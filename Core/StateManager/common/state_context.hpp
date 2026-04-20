#ifndef STATE_CONTEXT_HPP
#define STATE_CONTEXT_HPP

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include "stm32f7xx_hal.h"
#include "SBUS/sbus.h"
#include "sbus_rescaler.hpp"
#include "usart.h"
#include "gpio.h"
#include "ICM42688P/ICM42688P.h"

struct StateContext {

    uint32_t state_change_count = 0;
    std::function<void(const std::string&)> publish_log = [](const std::string&) {};

    // SBUS
    nokolat::SBUS            sbus_receiver;
    UART_HandleTypeDef*      sbus_uart  = &huart5;
    UART_HandleTypeDef*      debug_sbus_uart  = &huart2; // デバッグ用（必要に応じて変更）
    nokolat::RescaledSBUSData sbus_data = {};

    // ICM42688P（遅延初期化: InitStateでemplace）
    std::optional<ICM42688P> imu = std::nullopt;
};


#endif // STATE_CONTEXT_HPP
