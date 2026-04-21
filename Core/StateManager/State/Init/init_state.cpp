#include "../state_headers.hpp"
#include "../Config/sensor_config.hpp"

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
	}

	// センサーの設定
	context.imu->AccelConfig(context.imu->ACCEL_Mode::LowNoize, context.imu->ACCEL_SCALE::SCALE02g, context.imu->ACCEL_ODR::ODR01000hz, context.imu->ACCEL_DLPF::ODR40);
	context.imu->GyroConfig(context.imu->GYRO_MODE::LowNoize, context.imu->GYRO_SCALE::Dps0250, context.imu->GYRO_ODR::ODR01000hz, context.imu->GYRO_DLPF::ODR40);

    // EKF 遅延初期化
    context.ekf.emplace();
    AttitudeEKF_Init(&context.ekf.value(), SS_DT);

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
