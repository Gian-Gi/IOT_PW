//----- INCLUDE -----
#include <LiquidCrystal_I2C.h>  // Libreria LCD 16x2
#include <Wire.h>               // Necessita per LCD

//----- IMPOSTAZIONI -----
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE); // Setta gli indirizzi dell'LCD I2C
#define LMD35DZ_PIN 3   // Pin sensore analogico di temperatura

//----- SETUP -----
void setup()
{
  setta_lcd();          // Inizializza lo schermo LCD I2C
  setta_temp_aria();    // Inizializza la temperatura aria
}

//----- FUNZIONI -----
void setta_lcd()
{
  lcd.begin(16, 2);
  lcd.clear();
}

void setta_temp_aria()
{
  lcd.setCursor(0, 0);
  lcd.print("Temp.air");
  lcd.setCursor(14, 0);
  lcd.write(char(223)); // Carattere °
  lcd.write("C");
}

float leggi_temp_aria()
{
  // Il sensore analogico LM25DZ ha una temperatura rilevata di 10mV per °C.
  // I valori trasmessi vanno da 0 a 1023 e sono proporzionali a una tensione
  // che va da 0 a 5000mV (se alimentato a 5V)
  int sensor = analogRead(LMD35DZ_PIN);
  float millivolts = (sensor / 1023.0) * 5000;
  float celsius = millivolts / 10.0;
  return celsius;
}

//----- LOOP -----
void loop()
{
  float celsius = leggi_temp_aria();
  lcd.setCursor(9, 0);
  lcd.print(celsius);
  delay(1000);
}
