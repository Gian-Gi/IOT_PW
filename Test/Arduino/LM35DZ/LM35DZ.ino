//----- Sezione INCLUDE
#include <LiquidCrystal_I2C.h>  // Libreria LCD 16x2
#include <Wire.h> 

//----- Sezione IMPOSTAZIONI
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE); // Setta gli indirizzi dell'LCD I2C



const int LM35DZ = 3;     // Sensore analogico di temperatura
float celsius;
float millivolts;
int sensor;
String lcd_line1;
String lcd_line2;

void setup()
{
  lcd.begin(16, 2);         // Inizializza lo schermo LCD I2C seriale
  Serial.begin(9600);       // Inizializza la seriale
  setta_lcd();
}

void setta_lcd()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp.:");
}

void loop()
{
  sensor = analogRead(LM35DZ);            //Legge il sensore analogico
  millivolts = (sensor / 1023.0) * 5000;  //Calcola la tensione in millivolt
  celsius = millivolts / 10.0;            // Calcola la temperatura in Celsius
  // Stampa i dati di controllo
  lcd.setCursor(7, 0);
  lcd.print(celsius);
  lcd.setCursor(13, 0);
  lcd.write(char(223));     // Carattere °
  lcd.write("C");
  delay(1000);
}
