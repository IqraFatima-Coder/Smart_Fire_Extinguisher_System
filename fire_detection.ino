#include <SoftwareSerial.h>

// Pin Definitions
#define FLAME_SENSOR 2
#define GAS_SENSOR A0  // Now using analog pin A0
#define BUZZER 8
#define RELAY 7

bool alertSent = false;
int gasThreshold = 0;

void setup() {
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(RELAY, HIGH);

  Serial.begin(9600);

  delay(2000);  // Give time to initialize

  // Set gas threshold after warm-up
  int baseline = analogRead(GAS_SENSOR);
  gasThreshold = baseline + 40;  // Adjust as needed

  Serial.println("Smart Fire Extinguisher System Ready");
  Serial.print("Gas baseline: "); Serial.println(baseline);
  Serial.print("Gas threshold: "); Serial.println(gasThreshold);
}

void loop() {
  int flameDetected = digitalRead(FLAME_SENSOR);
  int gasValue = analogRead(GAS_SENSOR);
  bool gasDetected = gasValue > gasThreshold;

  Serial.print("Flame: "); Serial.print(flameDetected);
  Serial.print(" | Gas Value: "); Serial.print(gasValue);
  Serial.print(" | Threshold: "); Serial.println(gasThreshold);


  if (flameDetected == LOW || gasDetected) {
    digitalWrite(BUZZER, HIGH);
    delay(5000);
  } else {
    digitalWrite(BUZZER, LOW);
    delay(5000);
  }

  // 🔥 Confirmed flame detection
  if (flameDetected == LOW && !alertSent) {
    Serial.println("🔥 Flame detected. Verifying...");
    delay(2000);
    if (digitalRead(FLAME_SENSOR) == LOW) {
      digitalWrite(RELAY, LOW);
      alertSent = true;
      Serial.println("✅ Fire confirmed. Pump activated.");
    } else {
      Serial.println("❌ False flame alert.");
    }
  }

  // 💨 Confirmed gas detection
  if (gasDetected && !alertSent) {
    Serial.println("💨 Gas detected. Verifying...");
    delay(2000);
    int recheckGas = analogRead(GAS_SENSOR);
    if (recheckGas > gasThreshold) {
      digitalWrite(RELAY, LOW);
      alertSent = true;
      Serial.println("✅ Gas confirmed. Pump activated.");
    } else {
      Serial.println("❌ False gas alert.");
    }
  }

  // 🔁 Reset pump if both danger signals are gone
  if (flameDetected != LOW && analogRead(GAS_SENSOR) <= gasThreshold && alertSent) {
    delay(2000);
    if (digitalRead(FLAME_SENSOR) != LOW && analogRead(GAS_SENSOR) <= gasThreshold) {
      digitalWrite(RELAY, HIGH);
      alertSent = false;
      Serial.println("ℹ️ No danger. Pump deactivated.");
    }
  }

  // Communication with ESP8266
  if (gasDetected || flameDetected == LOW) {
    Serial.println("ALERT_TRIGGERED");
    delay(1000); // Prevent spamming
  }

  delay(100); // Stability delay
}
