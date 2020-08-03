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

int addVal = 1;
int recVal = 1;
int potVal = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

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
  lcd.init();
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
  potVal = map(potVal, 0, 1023, 0, 180);
  servo_setting();
  lcd_show(1, 0, "Rec:" + String(recVal) + " Servo:" + String(addVal), 1);
  lcd_show(0, 1, "Val:" + String(potVal), 50);

  if (upButton.isPressed())
  {
    pressedTime = millis();
  }

  if (upButton.isReleased())
  {
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration < SHORT_PRESS_TIME)
    {
      addVal++;
      if (addVal > 6)
      {
        addVal = 1;
      }
    }

    if (pressDuration > LONG_PRESS_TIME)
    {
      recVal++;
      if (recVal > 5)
      {
        recVal = 1;
      }
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
  switch (addVal)
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

void save_angle()
{
  int eeVal = addVal * recVal;
  EEPROM.write(eeVal, potVal);
  lcd_show(1, 0, "Save:" + String(potVal) + " to:" + String(eeVal), 1);
  lcd_show(0, 1, "Rec:" + String(recVal) + " Servo" + String(addVal), 750);
}

void run_servo()
{
  bool runStatus = true;
  int count = 1;
  while (runStatus)
  {
    okButton.loop();
    if (okButton.isPressed())
    {
      runStatus = false;
    }

    for (int i = 1; i < 7; i++)
    {
      i = i * count;
      int value = EEPROM.read(i);
      switch (i)
      {
      case 1:
        servo1.write(value);
        lcd_show(1, 0, "Rec:" + String(count), 1);
        lcd_show(0, 1, "Servo1:" + String(value), 250);
        break;
      case 2:
        servo2.write(value);
        lcd_show(1, 0, "Rec:" + String(count), 1);
        lcd_show(0, 1, "Servo2:" + String(value), 250);
        break;
      case 3:
        servo3.write(value);
        lcd_show(1, 0, "Rec:" + String(count), 1);
        lcd_show(0, 1, "Servo3:" + String(value), 250);
        break;
      case 4:
        servo4.write(value);
        lcd_show(1, 0, "Rec:" + String(count), 1);
        lcd_show(0, 1, "Servo4:" + String(value), 250);
        break;
      case 5:
        servo5.write(value);
        lcd_show(1, 0, "Rec:" + String(count), 1);
        lcd_show(0, 1, "Servo5:" + String(value), 250);
        break;
      case 6:
        servo6.write(value);
        lcd_show(1, 0, "Rec:" + String(count), 1);
        lcd_show(0, 1, "Servo6:" + String(value), 250);
        break;
      }
      count++;
      delay(250);
    }
  }
}