#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BACKLIGHT_PIN 3

LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);


OneWire  ds(10);  

void setup(void) {
  Serial.begin(9600);
   lcd.begin (16,2);
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(HIGH);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  if ( !ds.search(addr)) { 
  }
  for( i = 0; i < 8; i++) {
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      
      return;
  }
  Serial.println();
 
  switch (addr[0]) {
    case 0x10:
      
      type_s = 1;
      break;
    case 0x28:
     
      type_s = 0;
      break;
    case 0x22:
      
      type_s = 0;
      break;
    default:
      
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        
  
  delay(1000);     
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         
  
  for ( i = 0; i < 9; i++) {           
    data[i] = ds.read();
    
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; 
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  
    else if (cfg == 0x20) raw = raw & ~3; 
    else if (cfg == 0x40) raw = raw & ~1; 
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  lcd.print("  Temperature = ");
  lcd.setCursor(0, 0);
  lcd.print(celsius);
  lcd.print(" Celsius, ");
  lcd.setCursor(0, 1);
  lcd.print(fahrenheit);
  lcd.println(" Fahrenheit");
}
