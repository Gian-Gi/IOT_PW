//----- Sezione INCLUDE
#include <LiquidCrystal_I2C.h>  // Libreria LCD 16x2
#include <Wire.h> 

//----- Sezione IMPOSTAZIONI
const int ckAutoTest=2; // Porta per la verifica del collegamento devices
const int ldAutoTest=3; // Led verde autotest
int checkTest;
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE); // Setta gli indirizzi dell'LCD I2C



//const int LM35DZ = 0;     // Sensore analogico di temperatura
//float celsius;
//float millivolts;
//int sensor;

void setup()
{
  pinMode(ckAutoTest, INPUT);   // Inizializza IN autotest
  pinMode(ldAutoTest, OUTPUT);  // Inizializza OUT autotest
  lcd.begin(16, 2);             // Inizializza lo schermo LCD I2C seriale
  Serial.begin(9600);         // Inizializza la seriale
  if (checkArduino())
  {
    Serial.print("Check Arduino OK");
    //checkRaspberry()
  }
}

int checkArduino()
{
  bool returnCheck = false;
  lcd.home();
  lcd.print("CK Arduino .....");
  delay(2000);
  int autoTest = digitalRead(ckAutoTest);
  if (autoTest == 1)
  {
    digitalWrite(ldAutoTest, 1);
    lcd.home();
    lcd.print("CK Arduino .. OK"); 
    returnCheck = true;
  }
  else
  {
    lcd.home();
    lcd.print("CK Arduino  FAIL");
  }
  return returnCheck;
}

void loop()
{
  
//  delay(1000);
//  digitalWrite(ledAutoTest, 0);
  // Legge il sensore analogico
  //sensor = analogRead(LM35DZ);
  // Calcola la tensione in millivolt
  //millivolts = (sensor / 1023.0) * 5000;
  // Calcola la temperatura in Celsius
  //celsius = millivolts / 10.0;
  // Stampa i dati di controllo
//  Serial.print(sensor);
//  Serial.print(" ");
//  Serial.print(millivolts);
//  Serial.print(" ");
//  Serial.println(celsius);
  delay(1000);
}
