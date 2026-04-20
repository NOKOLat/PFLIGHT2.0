#ifndef SBUS_CONFIG_HPP
#define SBUS_CONFIG_HPP

#include <cstdint>

// ============================================================
// SBUS キャリブレーション設定
// 実機計測値に合わせて調整してください
// ============================================================
namespace SbusConfig {

	// ===== SBUSチャンネル =====
	static constexpr uint8_t CH_THROTTLE        = 3;
	static constexpr uint8_t CH_PITCH           = 0;
	static constexpr uint8_t CH_ROLL            = 1;
	static constexpr uint8_t CH_YAW             = 2;
	static constexpr uint8_t CH_DROP            = 4;
	static constexpr uint8_t CH_ARM             = 5;
	static constexpr uint8_t CH_SAFETY          = 6;
	static constexpr uint8_t CH_AUTO_MISSION    = 7;
	static constexpr uint8_t CH_PREFLIGHT_DEBUG = 8;
	static constexpr uint8_t CH_FLIGHT_DEBUG    = 9;

    // ===== SBUS 生値の基準範囲 =====
    static constexpr uint16_t SBUS_MIN = 360;
    static constexpr uint16_t SBUS_MID = 1024;
    static constexpr uint16_t SBUS_MAX = 1696;

    // ===== プロポのキャリブレーション =====

    static co



    // ===== スロットルのSBUS値範囲 =====
    static constexpr uint16_t THROTTLE_MIN = SBUS_MIN;
    static constexpr uint16_t THROTTLE_MAX = SBUS_MAX;

    // ===== 各軸のキャリブレーション値 =====
    static constexpr uint16_t PITCH_MIN         = SBUS_MIN;
    static constexpr uint16_t PITCH_MID         = SBUS_MID;
    static constexpr uint16_t PITCH_MAX         = SBUS_MAX;

    static constexpr uint16_t ROLL_MIN          = SBUS_MIN;
    static constexpr uint16_t ROLL_MID          = SBUS_MID;
    static constexpr uint16_t ROLL_MAX          = SBUS_MAX;

    static constexpr uint16_t YAW_MIN           = SBUS_MIN;
    static constexpr uint16_t YAW_MID           = SBUS_MID;
    static constexpr uint16_t YAW_MAX           = SBUS_MAX;

    // ===== 3段階スイッチの閾値 =====
    // LOW:  0    ~ SWITCH_LOW_THRESHOLD
    // MID:  SWITCH_LOW_THRESHOLD+1 ~ SWITCH_HIGH_THRESHOLD
    // HIGH: SWITCH_HIGH_THRESHOLD+1 ~ SBUS_MAX
    static constexpr uint16_t SWITCH_LOW_THRESHOLD  = 500;
    static constexpr uint16_t SWITCH_HIGH_THRESHOLD = 1500;

} // namespace SbusConfig

#endif // SBUS_CONFIG_HPP
