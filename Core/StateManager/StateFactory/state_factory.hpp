#ifndef STATE_FACTORY_HPP
#define STATE_FACTORY_HPP

#include <memory>
#include "../StateInterface/state_interface.hpp"
#include "../common/state_utility.hpp"
#include "../State/state_headers.hpp"


class StateFactory {

    public:

        static std::unique_ptr<StateInterface> createState(StateID state_id) {

            switch (state_id) {

                // --- 通常フロー ---
                case StateID::IDLE:
                    return std::make_unique<IdleState>();

                case StateID::STATE_A:
                    return std::make_unique<StateA>();

                case StateID::STATE_B:
                    return std::make_unique<StateB>();

                // --- エラー状態 ---
                case StateID::HARDWARE_ERROR:
                    return std::make_unique<HardwareErrorState>();

                // --- 緊急停止 ---
                case StateID::EMERGENCY_STOP:
                    return std::make_unique<EmergencyStopState>();

                default:
                    return std::make_unique<EmergencyStopState>();
            }
        }
};


#endif // STATE_FACTORY_HPP
