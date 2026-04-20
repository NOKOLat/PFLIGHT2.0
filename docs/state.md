状態は以下の表であらわされる

| 状態 | 説明 |
| --- | --- |
| `INIT` | 初期化 |
| `CALIBRATION` | キャリブレーション |
| `PreArm` | Arm待機 |
| `ARM` | Arm処理 |
| `PreFlight` | 飛行待機 |
| `Flight` | 手動飛行 |
| `AutoFlight` | 自動飛行 |
| `DisArm` | DisArm処理 |
| `Error` | エラー |

フォルダと状態クラスのcppファイルは以下のように分ける
```
Init        : InitState, CalibrationState, 
PreArm      : PreArmState, ArmState, PreFlightState, 
Flight      : FlightState, AutoFlight
PostFlight  : DisArmState
Error       : ErrorState
```

## Flightフォルダの状態について
stateinterfaceを継承したflightstatebaseクラスを作成し、
init()とupdate()などを純粋仮想関数として定義する。

この派生クラスになるflight, autoflightはonInit()とonUpdate()を実装し、init()とupdate()内でそれぞれ呼び出す

これにより2つの状態に共通処理を実装できる