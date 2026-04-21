# PWM処理の方法

[in] pid_output: PID制御の出力値(pitch, roll, yaw)
[in] throttle: スロットル値(0-100%)

[out] motor_pwm_output: モーターPWM出力値
[out] servo_pwm_output: サーボPWM出力値

## ドローンの構成ごとに変更するための戦略

実際に対応したいもの

### クワッドコプター

計算式:
```
motor_pwm_output[0] = throttle + pid_output[pitch] + pid_output[roll] + pid_output[yaw]
motor_pwm_output[1] = throttle + pid_output[pitch] - pid_output[roll] - pid_output[yaw]
motor_pwm_output[2] = throttle - pid_output[pitch] + pid_output[roll] - pid_output[yaw]
motor_pwm_output[3] = throttle - pid_output[pitch] - pid_output[roll] + pid_output[yaw]
``` 

### 2重反転オクタコプター

計算式:
```
motor_pwm_output[0] = throttle + pid_output[pitch] + pid_output[roll] + pid_output[yaw]
motor_pwm_output[1] = throttle + pid_output[pitch] - pid_output[roll] - pid_output[yaw]
motor_pwm_output[2] = throttle - pid_output[pitch] + pid_output[roll] - pid_output[yaw]
motor_pwm_output[3] = throttle - pid_output[pitch] - pid_output[roll] + pid_output[yaw]
motor_pwm_output[4] = throttle + pid_output[pitch] + pid_output[roll] - pid_output[yaw]
motor_pwm_output[5] = throttle + pid_output[pitch] - pid_output[roll] + pid_output[yaw]
motor_pwm_output[6] = throttle - pid_output[pitch] + pid_output[roll] + pid_output[yaw]
motor_pwm_output[7] = throttle - pid_output[pitch] - pid_output[roll] - pid_output[yaw]
```


### DualCopter

```
motor_pwm_output[0] = throttle;
motor_pwm_output[1] = throttle;
```

```
servo_pwm_output[0] = pid_output[pitch] + pid_output[roll] + pid_output[yaw]
servo_pwm_output[1] = pid_output[pitch] - pid_output[roll] - pid_output[yaw]
servo_pwm_output[2] = -pid_output[pitch] + pid_output[roll] - pid_output[yaw]
servo_pwm_output[3] = -pid_output[pitch] - pid_output[roll] + pid_output[yaw]
```