//----- INCLUDE -----
#include <LiquidCrystal_I2C.h>  // Libreria LCD 16x2
#include <Wire.h>               // Necessita per LCD
#include <DallasTemperature.h>  // Libreria sensore DS18B20
#include <OneWire.h>            // Necessita per DS18B20

//----- IMPOSTAZIONI -----
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE); // Setta gli indirizzi dell'LCD I2C
#define DS18B20_PIN 10                // Pin sensore digitale di temperatura
OneWire oneWire(DS18B20_PIN);         // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature ds18b20(&oneWire);  // Pass our oneWire reference to Dallas Temperature
DeviceAddress insideThermometer;      // Arrays to hold device address

//----- SETUP -----
void setup()
{
  setta_lcd();          // Inizializza lo schermo LCD I2C
  setta_temp_acqua();   // Inizializza la temperatura acqua
}

//----- FUNZIONI -----
void setta_lcd()
{
  lcd.begin(16, 2);
  lcd.clear();
}

void setta_temp_acqua()
{
  ds18b20.begin();
  ds18b20.getAddress(insideThermometer, 0);
  ds18b20.setResolution(insideThermometer, 12);
  lcd.setCursor(0, 1);
  lcd.print("Temp.wtr");
  lcd.setCursor(14, 1);
  lcd.write(char(223)); // Carattere °
  lcd.write("C");
}

float leggi_temp_acqua()
{
  ds18b20.requestTemperatures();  // Send the command to get temperatures
  float celsius = ds18b20.getTempC(insideThermometer);
  return celsius;
}

//----- LOOP -----
void loop()
{
  float celsius = leggi_temp_acqua();
  lcd.setCursor(9, 1);
  lcd.print(celsius);
  delay(1000);
}
