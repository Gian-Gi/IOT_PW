//----- INCLUDE -----
#include <LiquidCrystal_I2C.h>  // Libreria LCD 16x2
#include <Wire.h>               // Necessita per LCD

//----- IMPOSTAZIONI -----
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE); // Setta gli indirizzi dell'LCD I2C
#define CK_DEVICES_PIN 4  // Pin collegamento devices Arduino
#define LD_DEVICES_PIN 5  // Led autotest OK (verde)

//----- SETUP -----
void setup()
{
  setta_lcd();          // Inizializza lo schermo LCD I2C
  // Insert here the Arduino check
}

//----- FUNZIONI -----
void setta_lcd()
{
  lcd.begin(16, 2);
  lcd.clear();
}

void setta_ck_Arduino()
{
  pinMode(CK_DEVICES_PIN, INPUT);   // Inizializza IN autotest Arduino
  pinMode(LD_DEVICES_PIN, OUTPUT);  // Inizializza OUT autotest Arduino
  digitalWrite(LD_DEVICES_PIN, 0);
  lcd.setCursor(0, 0);
  lcd.print("CK devices .....");
}

bool check_Arduino()
{
  bool returnCheck = false;
  delay(2000);
  int autoTest = digitalRead(CK_DEVICES_PIN);
  if (autoTest)
  {
    lcd.setCursor(13, 0);
    lcd.print(" OK");
    digitalWrite(LD_DEVICES_PIN, 1);
    returnCheck = true;
  }
  else
  {
    lcd.setCursor(11, 0);
    lcd.print("FAIL!");
  }
  return returnCheck;
}

//----- LOOP -----
void loop()
{
  // ----->>>>> From here ...
  setta_ck_Arduino();
  if (check_Arduino())
  {
    // others checks
  }
  // ----->>>>> to here ... cut and copy in Setup function

  delay(2000);
  // others program lines
}
