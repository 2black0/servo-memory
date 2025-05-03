# 🤖 Servo Position Memory Controller

This project is a servo control system that allows storing and recalling multiple servo positions using EEPROM memory on an Arduino. It provides a user-friendly interface using buttons and an LCD, supporting **6 servo motors** and **5 memory slots per servo**.

Designed for applications such as robotic arms, animatronics, or teaching control systems, this project enables:
- Manual setting of servo positions via a potentiometer,
- Saving positions into EEPROM memory,
- Playback of stored positions,
- Navigation using simple push-button input with short/long press detection.

## 📦 Project Structure

```

.
├── Arduino
│   ├── libraries/             # Required Arduino libraries (Button, LCD I2C)
│   └── main.ino               # Core Arduino sketch for servo memory control
├── LICENSE                    # License file
└── README.md                  # This documentation

```

## 🛠 Features

- ✅ Supports 6 servo motors
- ✅ Up to 5 memory positions per servo
- ✅ EEPROM-based persistent storage
- ✅ 16x2 I2C LCD user interface
- ✅ Potentiometer-based angle setting
- ✅ Button interface with short/long press detection

## 🔧 Hardware Requirements

- Arduino Uno / Mega
- 6x Servo motors (e.g., SG90, MG996R)
- 1x Potentiometer (connected to A0)
- 2x Push buttons:
  - `UP` (Pin 2): select servo or memory record
  - `OK` (Pin 3): save position / play memory
- I2C LCD (16x2) display
- External power supply recommended for multiple servos
- Optional: pull-up/pull-down resistors for button inputs

## 🧠 How It Works

### Controls

- **UP Button:**
  - Short press: cycle through servo 1–6
  - Long press: cycle through memory record slots 1–5

- **OK Button:**
  - Short press: save current angle to EEPROM
  - Long press: play all 6 servo positions from the selected memory slot

### EEPROM Mapping

The memory is indexed using:  
`EEPROM Index = servoNumber * recordNumber`  
For 6 servos and 5 records each, EEPROM index ranges from 1 to 30.

### LCD Display

Two-line interface displays current servo and value:

```

Rec:1 Servo:3         ← Current record & selected servo
Val:135               ← Current angle set via potentiometer

```

## 📥 Library Dependencies

The following libraries are used:

- [Servo](https://www.arduino.cc/en/Reference/Servo)
- [ezButton](https://github.com/ArduinoGetStarted/ezButton) – debounced button handling
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- EEPROM (built-in)

Libraries are included in the `Arduino/libraries/` folder as `.zip`.

To install:
1. Open Arduino IDE
2. Go to **Sketch > Include Library > Add .ZIP Library**
3. Select each ZIP file provided

## 🚀 Getting Started

1. Connect all components according to your pin mapping
2. Upload `main.ino` to your Arduino
3. Use the potentiometer to set servo angle
4. Use UP/OK buttons to navigate and store values
5. Long press `OK` to play stored servo memory sequence

## 📸 Screenshots

> *(Add images of the setup or LCD display here for better understanding)*

## 👨‍💻 Author

Project by **[@2black0](https://github.com/2black0)**  
Email: `2black0@gmail.com`

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

> 💬 Contributions, issues, and suggestions are welcome! Feel free to open an issue or fork this project.