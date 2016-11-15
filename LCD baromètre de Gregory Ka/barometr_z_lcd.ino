
#include <Wire.h>
#include <BMP180.h>
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN 3
LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7, BACKLIGHT_PIN, POSITIVE); 

BMP180 barometer;

int indicatorLed = 13; 

float seaLevelPressure = 100700;

void setup()
{
  lcd.begin (16,2);
  Serial.begin(9600);
  
  Wire.begin();
  
  pinMode(indicatorLed, OUTPUT);
  
  barometer = BMP180();
  
  if(barometer.EnsureConnected())
  {
    Serial.println("Connected to BMP180."); 
    digitalWrite(indicatorLed, HIGH); 
     
    barometer.SoftReset();
    barometer.Initialize();
  }
  else
  { 
    Serial.println("Could not connect to BMP180.");
    digitalWrite(indicatorLed, LOW); 
  }
}

void loop()
{
  if(barometer.IsConnected)
  {
    
    long currentPressure = barometer.GetPressure();
     //lcd.setCursor(0, 1); //do sprawdzenia
    
    Serial.print("Pressure: ");
    Serial.print(currentPressure);  //wstawić/100 bedzue hPa
    Serial.print(" Pa");      //zmienić na hPa
    
    lcd.setCursor(0, 0);
    lcd.print(currentPressure/100);   //wstawić/100 bedzue hPa
    lcd.print(" hPa");             //zmienić na hPa
    
    float altitude = barometer.GetAltitude(seaLevelPressure);
    
    Serial.print("\tAltitude: ");
    Serial.print(altitude);
    Serial.print(" m");
    
    //lcd.setCursor(8, 1);
    //lcd.print(altitude);
    //lcd.print(" m");
    
    float currentTemperature = barometer.GetTemperature();
    
    Serial.print("\tTemperature: ");
    Serial.print(currentTemperature);
    Serial.write(176);
    Serial.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print(currentTemperature);
    lcd.print(" C");
    
    Serial.println(); // Start a new line.
    delay(1000); // Show new results every second.
  }
}
