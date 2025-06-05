
# 🔥 Smart Fire Extinguisher System

An IoT-based fire safety system integrating real-time fire and gas detection with automated suppression and email alerts. Built using Arduino (ATmega328P), ESP8266 Wi-Fi module, flame & gas sensors, relay-controlled pump, and email alert.

---

## 📌 Features

* 🔍 **Dual-Sensor Fire Detection** (IR Flame + MQ-2 Gas Sensor)
* 🚨 **Immediate Local Alert** via Buzzer
* 💧 **Automatic Fire Suppression** using Relay-Controlled Water Pump
* 📧 **Email Notifications** through ESP8266 using Gmail SMTP
* 🔁 **False Positive Mitigation** via sensor re-verification logic
* 🧪 **Tested Response Time**:

  * Detection: < 5 seconds
  * Email Alert: < 10 seconds

---

## 📂 Repository Structure

```
Smart-Fire-Extinguisher/
├── fire_detection.ino          # ATmega328P Firmware
├── email_notification.ino      # ESP8266 Firmware
├── Smart_Fire_Extinguisher_Project_Report.pdf
├── README.md                   # You're here!
```

---

## 🛠️ Hardware Components

| Component                          | Quantity  | Function                        |
| ---------------------------------- | --------- | ------------------------------- |
| Arduino UNO WiFi R3 (with ESP8266) | 1         | Main controller & communication |
| MQ-2 Gas Sensor                    | 1         | Smoke/Gas detection             |
| IR Flame Sensor                    | 1         | Flame detection                 |
| 5V Relay Module                    | 1         | Controls pump power             |
| 5V Mini Water Pump                 | 1         | Fire suppression                |
| Piezo Buzzer                       | 1         | Local audio alarm               |
| 7.4V Li-ion Battery                | 1         | Pump power source               |
| Breadboard + Jumper Wires          | as needed | Circuit connection              |

---

## ⚙️ Software Setup

### Prerequisites

* [Arduino IDE](https://www.arduino.cc/en/software)
* ESP8266 Board Package
* **Libraries:**

  * `ESP8266WiFi.h`
  * `ESP_Mail_Client.h`

---

### 🔧 Firmware Upload Instructions

#### Step 1: Upload `fire_detection.ino` to ATmega328P

1. Set DIP Switches: **Mode 1 (SW3, SW4 ON)**
2. Select board: `Arduino UNO`
3. Upload the code

#### Step 2: Upload `email_notification.ino` to ESP8266

1. Set DIP Switches: **Mode 2 (SW5, SW6, SW7 ON)**
2. Select board: `Generic ESP8266 Module` or compatible
3. Upload code with Wi-Fi and Gmail credentials



---

## 💡 System Workflow

1. Sensors continuously monitor environment.
2. On detection of flame or smoke:

   * Buzzer activates
   * Relay turns on water pump
   * ESP8266 receives alert over serial
   * Sends an emergency email to the recipient
3. System resets once environment is safe.

---

## 📧 Example Email Alert

> **Subject:** URGENT: Fire/Gas Detected!
> **Message:**
> 🚨 EMERGENCY ALERT 🚨
> Flame or dangerous gas detected! Immediate action required.

---

## 📽️ Demo Videos

📹 [Watch full system demo on OneDrive](https://1drv.ms/f/c/17379a8d00e56608/Elkq8_bAppNKhEwiy_Wv5YoBSW8DZHRFnPpKoW_WTOMAiQ?e=JV9ACz)

---

## 📄 Full Report

Please refer to the [`Smart_Fire_Extinguisher_Project_Report.pdf`](Smart_Fire_Extinguisher_Project_Report.pdf) file for detailed explanation, schematics, testing, and references.

---

## 🤝 Contribution

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

---

## 📜 License

This project is for educational purposes. Feel free to fork, modify, and use with credit.

---
