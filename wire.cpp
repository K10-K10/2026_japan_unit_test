#include <Arduino.h>

// --- 設定 ---
const int wire_pin = 19; // Wireサーボの信号線ピン (ARMIOの第3引数)
const int ledc_channel = 0;    // PWMチャンネル
const int pwm_freq = 50;       // サーボ標準の 50Hz
const int pwm_resolution = 16; // 16ビット解像度 (0-65535)

// --- パルス幅の設定 (マイクロ秒) ---
const int PULSE_TIGHT = 2400; // 引き締め状態 (2400us)
const int PULSE_SLACK = 500;  // 緩めた状態 (500us)

// マイクロ秒をDutyサイクル(0-65535)に変換する関数
uint32_t usToDuty(int us) {
  // 式: (us / 20000us) * 65535
  return (static_cast<uint32_t>(us) * 65535) / 20000;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("--- Wire Servo Solo Test ---");

  // PWMの設定
  ledcSetup(ledc_channel, pwm_freq, pwm_resolution);
  ledcAttachPin(wire_pin, ledc_channel);

  Serial.println("Setup Complete.");
}

void loop() {
  // 1. 引き締め (Tight)
  Serial.println("State: TIGHT (2400us)");
  ledcWrite(ledc_channel, usToDuty(PULSE_TIGHT));
  delay(2000);

  // 2. 緩める (Slack)
  Serial.println("State: SLACK (500us)");
  ledcWrite(ledc_channel, usToDuty(PULSE_SLACK));
  delay(2000);
}
