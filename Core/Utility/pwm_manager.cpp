#include "pwm_manager.hpp"
#include <cstdio>


bool PwmManager::checkMotors(std::initializer_list<uint8_t> indices) {

    for (uint8_t idx : indices) {

        // インデックス範囲チェック
        if (idx >= motors_.size()) {

            printf("[PwmManager] モーター インデックス %d が範囲外です\n", idx);
            return false;
        }

        // optional有効チェック・初期化チェック
        if (!motors_[idx].has_value() || !motors_[idx]->isInitialized()) {

            printf("[PwmManager] モーター %d が初期化されていません\n", idx);
            return false;
        }
    }

    return true;
}


bool PwmManager::checkServos(std::initializer_list<uint8_t> indices) {

    for (uint8_t idx : indices) {

        // インデックス範囲チェック
        if (idx >= servos_.size()) {

            printf("[PwmManager] サーボ インデックス %d が範囲外です\n", idx);
            return false;
        }

        // optional有効チェック・初期化チェック
        if (!servos_[idx].has_value() || !servos_[idx]->isInitialized()) {

            printf("[PwmManager] サーボ %d が初期化されていません\n", idx);
            return false;
        }
    }

    return true;
}
