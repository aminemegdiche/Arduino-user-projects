#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN 3
LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);

const char *monthName[12] = {
  "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze",
  "Lip", "Sie", "Wrz", "Paz", "Lis", "Gru"
};

const char *dayName[7] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thuesday", "Friday", "Saturday" };
  
byte nc1[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte nc2[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte nc3[8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111
};
byte nc4[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
  B10000
};
byte nc5[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111,
  B00011,
  B00001
};
byte nc6[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};

byte nc7[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};

byte nc8[8] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

int bigfont(int number, int pos){ 
  
 if(number == 1){
  
  lcd.setCursor(pos,1);
  lcd.write(6);
  lcd.setCursor(pos,2);
  lcd.write(" ");
  lcd.setCursor(pos,3);
  lcd.write(" ");
  lcd.setCursor(pos+1,1);
  lcd.write(8);
  lcd.setCursor(pos+1,2);
  lcd.write(" ");
  lcd.setCursor(pos+1,3);
  lcd.write(" ");
  lcd.setCursor(pos+2,1);
  lcd.write(1);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(1);

 } else 
  if(number == 2){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(" ");
  lcd.setCursor(pos,3);
  lcd.write(2);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(2);
  lcd.setCursor(pos+1,3);
  lcd.write(1);
  lcd.setCursor(pos+2,1);
  lcd.write(3);
  lcd.setCursor(pos+2,2);
  lcd.write(4);
  lcd.setCursor(pos+2,3);
  lcd.write(6);

  } else 
  if(number == 3 ){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(" ");
  lcd.setCursor(pos,3);
  lcd.write(5);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(8);
  lcd.setCursor(pos+1,3);
  lcd.write(6);
  lcd.setCursor(pos+2,1);
  lcd.write(3);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(4);

 }
 else 
  if(number == 4 ){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(1);
  lcd.setCursor(pos,3);
  lcd.write(" ");
  lcd.setCursor(pos+1,1);
  lcd.write(" ");
  lcd.setCursor(pos+1,2);
  lcd.write(6);
  lcd.setCursor(pos+1,3);
  lcd.write(" ");
  lcd.setCursor(pos+2,1);
  lcd.write(1);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(1);

   } else 
  if(number == 5 ){
  lcd.setCursor(pos,1);
  lcd.write(1);
  lcd.setCursor(pos,2);
  lcd.write(7);
  lcd.setCursor(pos,3);
  lcd.write(6);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(7);
  lcd.setCursor(pos+1,3);
  lcd.write(6);
  lcd.setCursor(pos+2,1);
  lcd.write(7);
  lcd.setCursor(pos+2,2);
  lcd.write(3);
  lcd.setCursor(pos+2,3);
  lcd.write(4);

 }
 else 
  if(number == 6 ){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(" ");
  lcd.setCursor(pos,3);
  lcd.write(5);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(8);
  lcd.setCursor(pos+1,3);
  lcd.write(6);
  lcd.setCursor(pos+2,1);
  lcd.write(3);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(4);

 }
 else 
  if(number == 7 ){
  lcd.setCursor(pos,1);
  lcd.write(7);
  lcd.setCursor(pos,2);
  lcd.write(" ");
  lcd.setCursor(pos,3);
  lcd.write(" ");
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(2);
  lcd.setCursor(pos+1,3);
  lcd.write(1);
  lcd.setCursor(pos+2,1);
  lcd.write(4);
  lcd.setCursor(pos+2,2);
  lcd.write(" ");
  lcd.setCursor(pos+2,3);
  lcd.write(" ");

 }
 else 
  if(number == 8 ){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(1);
  lcd.setCursor(pos,3);
  lcd.write(5);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(8);
  lcd.setCursor(pos+1,3);
  lcd.write(6);
  lcd.setCursor(pos+2,1);
  lcd.write(3);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(4);

 }
 else 
  if(number == 9 ){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(7);
  lcd.setCursor(pos,3);
  lcd.write(6);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(8);
  lcd.setCursor(pos+1,3);
  lcd.write(6);
  lcd.setCursor(pos+2,1);
  lcd.write(3);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(4);

 }
  else 
  if(number == 0 ){
  lcd.setCursor(pos,1);
  lcd.write(2);
  lcd.setCursor(pos,2);
  lcd.write(1);
  lcd.setCursor(pos,3);
  lcd.write(5);
  lcd.setCursor(pos+1,1);
  lcd.write(7);
  lcd.setCursor(pos+1,2);
  lcd.write(" ");
  lcd.setCursor(pos+1,3);
  lcd.write(6);
  lcd.setCursor(pos+2,1);
  lcd.write(3);
  lcd.setCursor(pos+2,2);
  lcd.write(1);
  lcd.setCursor(pos+2,3);
  lcd.write(4);

 }

  else 
  if(number == 61 ){
  lcd.setCursor(pos,1);
  lcd.write(6);
  lcd.setCursor(pos,3);
  lcd.write(7);
 }
 
  else 
  if(number == 62 ){
  lcd.setCursor(pos,1);
  lcd.write("");
  lcd.setCursor(pos,3);
  lcd.write("");
 }
};

void setup() {

   lcd.begin(20, 4);
   lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
   lcd.setBacklight(HIGH);
   lcd.createChar(1, nc1);
   lcd.createChar(2, nc2);
   lcd.createChar(3, nc3);
   lcd.createChar(4, nc4);
   lcd.createChar(5, nc5);
   lcd.createChar(6, nc6);
   lcd.createChar(7, nc7);
   lcd.createChar(8, nc8);
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    
  int br_hour = tm.Hour;
  int br_minute = tm.Minute;
  int array_h[2];
  int array_m[2];
  
  for (int i = 1;i>=0;i--){
    array_h[i] = br_hour % 10;
    br_hour = br_hour /= 10;
  }
  
   for (int ii = 1;ii>=0;ii--){
    array_m[ii] = br_minute % 10;
    br_minute = br_minute /= 10;
  }

  if(tm.Hour < 10){
  
    bigfont(0,0);
    bigfont(array_h[1],4);
  
  } else {
  
   bigfont(array_h[0],0);
   bigfont(array_h[1],4);
  
  }
  
  bigfont(61, 8);
  
  if(tm.Minute < 10){
  
    bigfont(0,10);
    bigfont(array_m[1],14);
  
  } else {
  
   bigfont(array_m[0],10);
   bigfont(array_m[1],14);
  
  }
    lcd.setCursor(18,3);
    LCDprint2digits(tm.Second);
    lcd.setCursor (0, 0);
    lcd.print(tm.Day);
    lcd.print('/');
    LCDm2d(tm.Month);
    lcd.print('/');
    lcd.print(tm.Year-30);
    lcd.print(" ");
    lcd.print(dayName[tm.Wday]);
    
  if(tm.Wday==0){
    lcd.setCursor(18, 1);lcd.print(":|");
  };
  if(tm.Wday==1){
    lcd.setCursor(18, 1);lcd.print(":(");
  };
  if(tm.Wday==6){
    lcd.setCursor(18, 1);lcd.print(":D");
  };
  if(tm.Wday==5){
    lcd.setCursor(18, 1);lcd.print(":)");
  };

    
  } else {
    if (RTC.chipPresent()) {
      lcd.println("DS1307 stoi. Uruchom Zegar");
      } 
       else {
      lcd.println("DS1307 blad oczczytu!");
      lcd.println("sprawdz polaczenie");
    }
    delay(9000);
  }
  delay(1000);
}

//void print2digits(int number) {
//  if (number >= 0 && number < 10) {
//    Serial.write('0');
//  }
//  Serial.print(number);
//}
  
void LCDprint2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);  
}

 void LCDm2d(int month_with0){
if(month_with0 > 0 && month_with0 < 10){
  lcd.write('0');}
  lcd.print(month_with0);
  }
