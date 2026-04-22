#include "../state_headers.hpp"
#include "../Config/sensor_config.hpp"
#include "../../../Utility/PwmManager/quadcopter_pwm_manager.hpp"

// icm42688p用のSPI書き込み関数
static uint8_t icm_spi_write(uint8_t reg_addr, uint8_t* tx_buffer, uint8_t len) {

    uint8_t cmd = reg_addr & 0x7Fu; // MSB=0: write
    HAL_GPIO_WritePin(SensorConfig::ICM42688P::CS_PORT, SensorConfig::ICM42688P::CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SensorConfig::ICM42688P::SPI_HANDLE, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(SensorConfig::ICM42688P::SPI_HANDLE, tx_buffer, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SensorConfig::ICM42688P::CS_PORT, SensorConfig::ICM42688P::CS_PIN, GPIO_PIN_SET);
    return 0;
}

// icm42688p用のSPI読み取り関数
static uint8_t icm_spi_read(uint8_t reg_addr, uint8_t* rx_buffer, uint8_t len) {

    uint8_t cmd = reg_addr | 0x80u; // MSB=1: read
    HAL_GPIO_WritePin(SensorConfig::ICM42688P::CS_PORT, SensorConfig::ICM42688P::CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SensorConfig::ICM42688P::SPI_HANDLE, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(SensorConfig::ICM42688P::SPI_HANDLE, rx_buffer, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SensorConfig::ICM42688P::CS_PORT, SensorConfig::ICM42688P::CS_PIN, GPIO_PIN_SET);
    return 0;
}

// icm42688p用のログ関数
static void icm_log(const char* msg) {

    printf("[ICM42688P] %s\n", msg);
}


StateError InitState::init(StateContext& context) {

	// icm42688pの初期化
    context.imu.emplace(icm_spi_write, icm_spi_read, icm_log);
    
    // 通信チェック
	if(context.imu->Connection()){

		printf("ICM42688p Not Found\n");
        return StateError::UPDATE_FAILED_CRITICAL;
	}

	// センサーの設定
    if(context.imu->AccelConfig(::ICM42688P::ACCEL_Mode::LowNoize, ::ICM42688P::ACCEL_SCALE::SCALE02g, ::ICM42688P::ACCEL_ODR::ODR01000hz, ::ICM42688P::ACCEL_DLPF::ODR40) != 0){

		printf("ICM42688p Accel Config Failed\n");
        return StateError::UPDATE_FAILED_CRITICAL;
	}
    if(context.imu->GyroConfig(::ICM42688P::GYRO_MODE::LowNoize, ::ICM42688P::GYRO_SCALE::Dps0250, ::ICM42688P::GYRO_ODR::ODR01000hz, ::ICM42688P::GYRO_DLPF::ODR40) != 0){

		printf("ICM42688p Gyro Config Failed\n");
        return StateError::UPDATE_FAILED_CRITICAL;
	}

    // EKF 遅延初期化
    context.ekf.emplace();
    if (AttitudeEKF_Init(&context.ekf.value(), SS_DT) != 0) {

        printf("EKF Init Failed\n");
        return StateError::UPDATE_FAILED_CRITICAL;
    }

    // PwmManager 初期化（4発機: QuadcopterPwmManager）
    context.pwm_manager = std::make_unique<QuadcopterPwmManager>();

    if (!context.pwm_manager->init()) {

        printf("[InitState] PwmManagerの初期化に失敗しました\n");
        return StateError::UPDATE_FAILED_CRITICAL;
    }

    // CascadePIDManager 初期化（FlightStateで使用）
    context.cascade_pid_manager = std::make_unique<CascadePIDManager>(SS_DT);

    return StateError::NONE;
}


StateError InitState::update(StateContext& context) {

    return StateError::NONE;
}


StateResult InitState::evaluateNextState(StateContext& context) {

    return {StateChange::STATE_CHANGE, StateID::CALIBRATION};
}


StateID InitState::getStateID() const {

    return StateID::INIT;
}
