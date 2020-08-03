/*
6 Servo Memories
by 2black0@gmail.com
*/

#include <Servo.h>
#include <ezButton.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

#define potPin A0
#define upBtnPin 2
#define okBtnPin 3
#define servo1Pin 8
#define servo2Pin 9
#define servo3Pin 10
#define servo4Pin 11
#define servo5Pin 12
#define servo6Pin 13

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

ezButton upButton(upBtnPin);
ezButton okButton(okBtnPin);

unsigned long pressedTime = 0;
unsigned long releasedTime = 0;
const int SHORT_PRESS_TIME = 1000;
const int LONG_PRESS_TIME = 1000;

int address = 0;
int potVal = 0;

iquidCrystal_I2C lcd(0x27, 16, 2);

void init_servo()
{
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  servo6.attach(servo6Pin);
}

void init_button()
{
  upButton.setDebounceTime(50);
  okButton.setDebounceTime(50);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  init_servo();
  init_button();
  delay(100);

  lcd_show(1, 0, "Servo Memories", 1);
  lcd_show(0, 0, "by 2black0", 1000);
}

void loop()
{
  upButton.loop();
  okButton.loop();

  potVal = analogRead(potPin);
  potVal = map(potVal, 0, 1023, 10, 180);
  lcd_show(1, 0, "Servo:" + String(int(address + 1)), 1);
  lcd_show(0, 1, "Value:" + String(potVal), 50);
  servo_setting();

  if (upButton.isReleased())
  {
    address++;
    if (address > 5)
    {
      address = 0;
    }
  }

  if (okButton.isPressed())
  {
    pressedTime = millis();
  }

  if (okButton.isReleased())
  {
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration < SHORT_PRESS_TIME)
      save_angle(potVal);

    if (pressDuration > LONG_PRESS_TIME)
      run_servo();
  }
}

void lcd_show(bool clear, int line, String text, int timedelay)
{
  if (clear)
  {
    lcd.clear();
  }
  lcd.setCursor(0, line);
  lcd.print(text);
  Serial.println(text);
  delay(timedelay);
}

void servo_setting()
{
  switch (int(address + 1))
  {
  case 1:
    servo1.write(potVal);
    break;
  case 2:
    servo2.write(potVal);
    break;
  case 3:
    servo3.write(potVal);
    break;
  case 4:
    servo4.write(potVal);
    break;
  case 5:
    servo5.write(potVal);
    break;
  case 6:
    servo6.write(potVal);
    break;
  }
}

void save_angle(int potVal)
{
  int servoVal = potVal;
  EEPROM.write(address, servoVal);
  lcd_show(1, 0, "Save:" + String(servoVal), 1);
  lcd_show(0, 1, "Servo" + String(int(address + 1)), 1000);
}

void run_servo()
{
  bool runStatus = true;
  while (runStatus)
  {
    okButton.loop();
    if (okButton.isPressed())
    {
      runStatus = false;
    }

    for (int i = 0; i < 6; i++)
    {
      int value = EEPROM.read(i + 1);
      switch (i)
      {
      case 1:
        servo1.write(value);
        lcd_show(1, 0, "Servo1 to:" + String(value), 250);
        break;
      case 2:
        servo2.write(value);
        lcd_show(1, 0, "Servo2 to:" + String(value), 250);
        break;
      case 3:
        servo3.write(value);
        lcd_show(1, 0, "Servo3 to:" + String(value), 250);
        break;
      case 4:
        servo4.write(value);
        lcd_show(1, 0, "Servo4 to:" + String(value), 250);
        break;
      case 5:
        servo5.write(value);
        lcd_show(1, 0, "Servo5 to:" + String(value), 250);
        break;
      case 6:
        servo6.write(value);
        lcd_show(1, 0, "Servo6 to:" + String(value), 250);
        break;
      }

      delay(250);
    }
  }
}