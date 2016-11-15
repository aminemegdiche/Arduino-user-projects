#include "DHT.h"          // biblioteka DHT
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN 3

LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);

#define DHTPIN 2          // numer pinu sygnałowego
 
DHT dht;                  // definicja czujnika
 
void setup()
{
  Serial.begin(9600);     // otworzenie portu szeregowego
  dht.setup(DHTPIN);      // inicjalizacja czujnika
  // dht.setup(DHTPIN, DHT11);      // inicjalizacja czujnika DHT11
  // dht.setup(DHTPIN, DHT22);      // inicjalizacja czujnika DHT12
  lcd.begin (16,2);
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(HIGH);

}
 
void loop()
{
  // Miniamalne opóźnienie odczytu
  delay(dht.getMinimumSamplingPeriod());
 
  // Odczyt temperatury i wilgotności powietrza
  float t = dht.getTemperature();
  float h = dht.getHumidity();
 
  // Sprawdzamy poprawność danych
  if (dht.getStatus())
  {
    // Jeśli nie, wyświetlamy informację o błędzie
    lcd.println("Blad odczytu danych z czujnika");
  } else
    // Jeśli tak, wyświetlamy wyniki pomiaru
    lcd.setCursor(0, 0);
    lcd.print("Wilgoc: ");
    lcd.print(h);
    lcd.print(" % ");
    lcd.setCursor(1, 1);
    lcd.print("Tempe: ");
    lcd.print(t);
    lcd.print(" C  ");
    
 }
