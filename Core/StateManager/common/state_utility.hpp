#ifndef STATE_UTILITY_HPP
#define STATE_UTILITY_HPP

#include <cstdint>

enum class StateID : uint8_t {

    IDLE             = 0,
    STATE_A          = 1,   
    STATE_B          = 2,   
    HARDWARE_ERROR   = 20, 
    EMERGENCY_STOP   = 30,  
    INVALID_STATE    = 255
};

// 状態遷移のエラーコード
enum class StateError : uint8_t {

    NONE                        = 0,
    UPDATE_FAILED_RECOVERABLE   = 1,
    UPDATE_FAILED_CRITICAL      = 2,
    CRITICAL_STOPPED            = 3
};

// 遷移フラグ
enum class StateChange : uint8_t {

    NO_STATE_CHANGE = 0,
    STATE_CHANGE    = 1
};

// 状態遷移の成功/失敗（changeState() の戻り値）
enum class StateChangeResult : uint8_t {

    SUCCESS = 0,
    FAILED  = 1,
};

// update() の処理継続/シャットダウン（StateManager::update() の戻り値）
enum class UpdateResult : uint8_t {

    CONTINUE = 0,
    SHUTDOWN = 1,
};

// update() の戻り値（遷移情報）
struct StateResult{

    StateChange change;
    StateID     next_state;
    StateError  error = StateError::NONE;
};


// ログ用ヘルパー
inline const char* StateIDToString(StateID state_id) {

    switch (state_id) {

        case StateID::IDLE:           return "IDLE";
        case StateID::STATE_A:        return "STATE_A";
        case StateID::STATE_B:        return "STATE_B";
        case StateID::HARDWARE_ERROR: return "HARDWARE_ERROR";
        case StateID::EMERGENCY_STOP: return "EMERGENCY_STOP";
        case StateID::INVALID_STATE:  return "INVALID_STATE";
        default:                      return "UNKNOWN_STATE";
    }
}

#endif // STATE_UTILITY_HPP
