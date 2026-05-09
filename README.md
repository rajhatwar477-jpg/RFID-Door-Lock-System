# 🔐 RFID Door Lock System

An Arduino-based door access control system using RFID card authentication.

## 📦 Components Used
| Component        | Quantity |
|-----------------|----------|
| Arduino Uno/Nano | 1        |
| MFRC522 RFID Module | 1   |
| 5V Relay Module  | 1        |
| Buzzer           | 1        |
| Green LED        | 1        |
| Red LED          | 1        |
| Push Button (Exit) | 1      |

## 🔌 Pin Connections
| Component     | Arduino Pin |
|--------------|-------------|
| RFID SS      | 10          |
| RFID RST     | 9           |
| Relay        | 3           |
| Buzzer       | 2           |
| Green LED    | 5           |
| Red LED      | 6           |
| Exit Button  | 4           |

## ⚙️ Libraries Required
- `SPI.h` (built-in)
- `MFRC522` – Install via Arduino Library Manager

## 🚀 How It Works
- Scan an authorized RFID card → Green LED + Relay unlocks door
- Scan unauthorized card → Red LED + Buzzer alarm
- Press Exit button → Unlocks door from inside

## 🔧 Setup
1. Install the `MFRC522` library
2. Add your card UIDs to the `allowedCards[]` array
3. Upload to Arduino and power on

## 📄 License
