#include "state_manager.hpp"
#include "../StateFactory/state_factory.hpp"
#include "isr_manager.hpp"
#include <cstdio>


StateManager::StateManager(StateID init_state_id): init_state_id_(init_state_id) {

    // ログ関数の定義
    state_context_.publish_log = [](const std::string& msg) {

        printf("%s\n", msg.c_str());
    };
}


// 初期化処理（最初に1回だけ呼ばれる）
// コンストラクタで渡された初期状態のセットアップ
// フォールバック用の状態の生成を行う
bool StateManager::init() {

    // fallback_emergency_stop_ の生成
    fallback_emergency_stop_ = StateFactory::createState(StateID::EMERGENCY_STOP);

    // fallback_emergency_stop_ のチェック
    if (!fallback_emergency_stop_) {

        // 生成失敗 → ログを出して false を返す
        state_context_.publish_log("[StateManager] CRITICAL: Failed to create EMERGENCY_STOP. Halting.");
        return false;
    }

    // ISRManager に SBUS を登録し、DMA受信を開始する
    ISRManager::registerSBUS(&state_context_.sbus_receiver, state_context_.sbus_uart);

    // 初期状態への遷移
    return changeState(init_state_id_) == StateChangeResult::SUCCESS;
}

// 更新処理（メインループから毎フレーム呼ばれる）
// EMERGENCY_STOP で停止処理が完了した場合のみ SHUTDOWN を返す
UpdateResult StateManager::update() {

    // エラー時のフォールバック処理
    // EMERGENCY_STOP の停止処理を実行し、完了したら SHUTDOWN を返す
    if(use_fallback_) {

        // フォールバック中は fallback_emergency_stop_ が持っている EMERGENCY_STOP 状態を使用する
        StateError fallback_error = fallback_emergency_stop_->update(state_context_);

        // EMERGENCY_STOP の停止処理が完了 → シャットダウン
        if (fallback_error == StateError::CRITICAL_STOPPED) {

            state_context_.publish_log("[StateManager] Emergency stop completed. Shutting down.");
            return UpdateResult::SHUTDOWN;
        }

        // フォールバック中は常に CONTINUE を返す（EMERGENCY_STOP の停止完了を待つ）
        return UpdateResult::CONTINUE;
    }

    // current_state_ の update() を呼ぶ
    StateError update_error = current_state_->update(state_context_);

    if(update_error == StateError::UPDATE_FAILED_CRITICAL) {

        // フォールバックフラグを立てる
        state_context_.publish_log("[StateManager] CRITICAL: State update failed (ID: " + std::string(StateIDToString(current_state_->getStateID())) + ")");
        state_context_.publish_log("[StateManager] Falling back to EMERGENCY_STOP");
        use_fallback_ = true;

        return UpdateResult::CONTINUE;
    }

    // 遷移判定
    StateResult result = current_state_->evaluateNextState(state_context_);

    // 状態遷移発生時の処理
    if (result.change == StateChange::STATE_CHANGE) {

        // 生成に失敗した場合はフォールバックフラグを立てる
        // フォールバック処理をするため、常に CONTINUE を返す
        if(changeState(result.next_state) == StateChangeResult::FAILED) {

            use_fallback_ = true;
            return UpdateResult::CONTINUE;
        }
    }

    return UpdateResult::CONTINUE;
}

// 状態遷移処理: 指定された state_id に遷移する
// 成功: StateChangeResult::SUCCESS を返す
// 失敗: StateChangeResult::FAILED を返す
StateChangeResult StateManager::changeState(StateID state_id) {

    // インスタンス生成
    std::unique_ptr<StateInterface> new_state = StateFactory::createState(state_id);

    // 生成失敗
    if (!new_state) {

        state_context_.publish_log("[StateManager] Failed to create state instance (ID: " + std::to_string(static_cast<int>(state_id)) + ")");
        return StateChangeResult::FAILED;
    }

    // 状態の初期化
    StateError init_error = new_state->init(state_context_);

    // 初期化失敗
    if (init_error != StateError::NONE) {

        state_context_.publish_log("[StateManager] State init() failed (ID: " + std::string(StateIDToString(state_id)) + ")");
        return StateChangeResult::FAILED;
    }

    // 遷移成功：current_state_ をセット
    current_state_ = std::move(new_state);
    state_context_.publish_log("[StateManager] -> " + std::string(StateIDToString(state_id)));

    return StateChangeResult::SUCCESS;
}

// StateContext へのアクセス
StateContext& StateManager::getContext() {

    return state_context_;
}

// 現在の状態 ID を取得
StateID StateManager::getCurrentStateID() const {

    if (!current_state_) {

        return StateID::INVALID_STATE;
    }

    return current_state_->getStateID();
}
