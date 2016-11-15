#include <LiquidCrystal.h>

#include <DS18B20.h>

#include <OneWire.h>

LiquidCrystal lcd(12,11,5,4,3,2);
OneWire onewire(7);
DS18B20 sensor(&onewire);

byte address[8] = {0x28, 0xA5, 0xE8, 0x74, 0x6, 0x0, 0x0, 0x3A};

void setup() {
  sensor.begin();
  lcd.begin(16,2);
  lcd.print("Swiatlo:");
  lcd.setCursor (0,1);
  lcd.print("Temp.:");
  lcd.setCursor (14,0);
  lcd.print("%");
  lcd.setCursor (12,1);
  lcd.print("'C");
  sensor.request(address);
}

void loop() {
  int sensorValue = analogRead(A0);
  float swiatlo = sensorValue * (100.0 / 1023.0);
  lcd.setCursor (9,0);
  lcd.print(swiatlo);
  if (sensor.available())
  {
    float temperature = sensor.readTemperature(address);
    lcd.setCursor (7,1);
    lcd.print(temperature);
    
    sensor.request(address);
  }
  delay (500);
}
