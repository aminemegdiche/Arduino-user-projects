#include <DS1307RTC.h>
#include <Time.h>
#include <pitches.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <VirtualWire.h>
#define BACKLIGHT_PIN 3
LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);

const char *monthName[12] = {
  "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze",
  "Lip", "Sie", "Wrz", "Paz", "Lis", "Gru"
};

const char *dayName[7] = {
"Monday", "Tuesday", "Wednesday", "Thuesday", "Friday", "Saturday",  "Sunday" };
  
int czas_h;
int czas_m;
int alarm_h = 0;
int alarm_m = 0;
boolean alarm_on = false;
boolean sygnal = false;
boolean snooze = false;
boolean a_stan = false;
int LED=5;
int sn_time = 1;
  
byte nc1[8]={
B00000,
B00000,
B00000,
B00000,
B11111,
B11111,
B11111,
B11111
};
byte nc2[8]={
B11111,
B11111,
B11111,
B11111,
B00000,
B00000,
B00000,
B00000
};
byte nc3[8]={
B00000,
B00000,
B11111,
B11111,
B11111,
B11111,
B00000,
B00000
};
byte nc4[8]={
B00001,
B00011,
B00111,
B01111,
B11111,
B11111,
B11111,
B11111
};
byte nc5[8]={
B10000,
B11000,
B11100,
B11110,
B11111,
B11111,
B11111,
B11111
};
byte nc6[8]={
B11111,
B11111,
B11111,
B11111,
B01111,
B00111,
B00011,
B00001
};
byte nc7[8]={
B11111,
B11111,
B11111,
B11111,
B11110,
B11100,
B11000,
B10000
};
byte nc8[8]={
B11111,
B11110,
B11100,
B11000,
B11000,
B11100,
B11110,
B11111
};

int bigfont(int number, int pos){ 

int n[13][3][3]={
{{4,2,5},{255,254,255},{6,1,7}},
{{4,255,254},{254,255,254},{254,255,254}},
{{4,2,5},{254,4,7},{4,255,1}},
{{4,2,5},{254,3,8},{6,1,7}},
{{4,254,1},{255,1,255},{254,254,255}},
{{255,2,2},{2,2,5},{1,1,7}},
{{4,2,5},{255,3,1},{6,1,7}},
{{2,2,7},{254,4,254},{254,255,254}},
{{4,2,5},{255,3,255},{6,1,7}},
{{4,2,5},{2,3,255},{1,1,7}},
{{254,1,254},{254,254,254},{254,2,254}},
{{254,254,254},{254,254,254},{254,254,254}},
{{254,4,255},{254,254,255},{254,254,255}}
};

  lcd.setCursor(pos,1);
  lcd.write(n[number][0][0]);
  lcd.setCursor(pos,2);
  lcd.write(n[number][1][0]);
  lcd.setCursor(pos,3);
  lcd.write(n[number][2][0]);
  lcd.setCursor(pos+1,1);
  lcd.write(n[number][0][1]);
  lcd.setCursor(pos+1,2);
  lcd.write(n[number][1][1]);
  lcd.setCursor(pos+1,3);
  lcd.write(n[number][2][1]);
  lcd.setCursor(pos+2,1);
  lcd.write(n[number][0][2]);
  lcd.setCursor(pos+2,2);
  lcd.write(n[number][1][2]);
  lcd.setCursor(pos+2,3);
  lcd.write(n[number][2][2]);
};

void setup() {
   vw_setup(2000);	 
   vw_set_rx_pin(4);
   vw_rx_start();     
   lcd.begin(20, 4);
   lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
   lcd.setBacklight(HIGH);
   Serial.begin(9600);
   pinMode(A0, INPUT);
   pinMode(3, OUTPUT);//buzzer
   pinMode(A1, INPUT);
   pinMode(11, OUTPUT);
   pinMode(LED, OUTPUT);
   digitalWrite(11, LOW);
   pinMode(10, INPUT);
   pinMode(9, INPUT);
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
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

if (vw_get_message(buf, &buflen)) 
    {
       String stan;
  	for (int i = 0; i < buflen; i++)
        { 
        stan +=char(buf[i]);
        }
     if ( stan =="on") {
  lcd.clear();
  sygnal = false;
  snooze = false;
  a_stan = false;
  alarm_on = false;
  noTone(12);
   }
   else {noTone(12);}
 }
 
  int ar_h = map(analogRead(A0), 0, 1023, 0, 24);
  int ar_m = map(analogRead(A1), 0, 1023, 0, 60);
  int dr_a = digitalRead(10);
  int dr_s = digitalRead(9);
  int astop = digitalRead(8);
  String s0 = ":";
  String s1 = "A0(HOUR):";
  String s2 = ", A1(MIN):";
  String s3 = ", SetAlarm(10):";
  String s4 = ", Snooze(9):";
  String s5 = ", Czas:";
  String s6 = ", Alarm:";
  String s7 = ", a_stan:";
  String s8 = ", Sygnal:";
  String s9 = ", Alarm_ON:";
  String sprint = s1 + ar_h + s2 + ar_m + s3 + dr_a + s4 + dr_s + s5 + String(czas_h) + s0 + String(czas_m) + s6+ String(alarm_h) + s0 +String(alarm_m) +s7 + a_stan + s8 + sygnal + s9 + alarm_on;
  Serial.println(sprint);
  tmElements_t tm;  
  
  if(sygnal == false && snooze == false){
  if(dr_a==1){
  delay(20);
  lcd.clear();
  a_stan =! a_stan;
  alarm_on =! alarm_on;
  delay(20);
  };
  };

  if (a_stan == true){
  alarm_on = false;
  alarm_h = ar_h;
  alarm_m = ar_m;
  int br_ahour = ar_h;
  int br_aminute = ar_m;
  int array_ah[2];
  int array_am[2];
  
 if(sn_time < 10){
  lcd.setCursor(15,0);
  lcd.print("SD:");
  lcd.setCursor(19,0);
  lcd.print(sn_time);
  lcd.setCursor(18,0);
  lcd.write(254);
 }else {
  lcd.setCursor(18,0);
  lcd.print(sn_time);}

if(dr_s == HIGH){
  if(sn_time < 10){
  sn_time = sn_time +1;
}
  else if(sn_time >= 10 && sn_time<30){
  sn_time = sn_time +5;
}
  else if(sn_time >= 30){
  sn_time = 1;
};}
  
  
  for (int j = 1;j>=0;j--){
    array_ah[j] = br_ahour % 10;
    br_ahour = br_ahour /= 10;
  };
  
   for (int jj = 1;jj>=0;jj--){
    array_am[jj] = br_aminute % 10;
    br_aminute = br_aminute /= 10;
  };

  if(ar_h < 10){
  
    bigfont(0,0);
    bigfont(array_ah[1],4);
  
  } else {
  int aone;
    if(array_ah[0]==1){
      aone = 12;
  } else{aone = array_ah[0];};
   bigfont(aone,0);
   bigfont(array_ah[1],4);
  
  }
  
  bigfont(10, 7);
  
  if(ar_m < 10){
  
    bigfont(0,10);
    bigfont(array_am[1],14);
  
  } else {
  int aone;
    if(array_am[0]==1){
      aone = 12;
  } else{aone = array_am[0];}
   bigfont(aone,10);
   bigfont(array_am[1],14);
  }
  
    lcd.setCursor (0, 0);
    lcd.print("ALARM SET:");
 
 if (alarm_h >= 0 && alarm_h< 9){
    lcd.setCursor (18, 3);
    lcd.print(":("); }
 else if(alarm_h >=9 && alarm_h <23){
    lcd.setCursor (18, 3);
    lcd.print(":)"); }
    
 lcd.setCursor(18,1);
 lcd.print("A");
 lcd.setCursor(19,1);
 lcd.write(1); 
    
    
  }else{
   
  if(alarm_h == czas_h && alarm_m == czas_m && alarm_on == true){
     sygnal = true;
  };
   
  if(sygnal == true){
    
tone(12,50);
  
    
    if(dr_s == HIGH){
      
      digitalWrite(11, LOW);
      if (alarm_m <=59){
      alarm_m = alarm_m + sn_time;}
      
     if (alarm_m > 59){
       alarm_m = alarm_m - 60;
       if(alarm_h <= 23){
       alarm_h = alarm_h + 1;
       }
       if(alarm_h >=24){
       alarm_h=0;
      }
    }
      sygnal = false;
      snooze = true;
      noTone(12);
    };
    
  } 

  if (RTC.read(tm)) {
  czas_h = tm.Hour;
  czas_m = tm.Minute;
  int br_hour = tm.Hour;
  int br_minute = tm.Minute;
//  int br_hour = tm.Hour;
//  int br_minute = tm.Minute;
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
  int one;
    if(array_h[0]==1){
      one = 12;
  } else{one = array_h[0];}
   bigfont(one,0);
   bigfont(array_h[1],4);
  
  }
  
  bigfont(10, 7);
  
  if(tm.Minute < 10){
  
    bigfont(0,10);
    bigfont(array_m[1],14);
  
  } else {
  int one;
    if(array_m[0]==1){
      one = 12;
  } else{one = array_m[0];}
   bigfont(one,10);
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
    lcd.print(dayName[tm.Wday-1]);
    
  if(tm.Wday==7){
    lcd.setCursor(18, 0);lcd.print(":|");
  };
  if(tm.Wday==1){
    lcd.setCursor(18, 0);lcd.print(":(");
  };
  if(tm.Wday==6){
    lcd.setCursor(18, 0);lcd.print(":D");
  };
  if(tm.Wday==5){
    lcd.setCursor(18, 0);lcd.print(":)");
  };
  
    if(alarm_on == true){
    lcd.setCursor(18,1);
    lcd.print("A");
    lcd.setCursor(19,1);
    lcd.write(1);
  } else {
    lcd.setCursor(18,1);
    lcd.print("A");
    lcd.setCursor(19,1);
    lcd.write(2);
  }
  
  
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
  
  //delay(900);
 // bigfont(11, 7);
  delay(20);
  };
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
  };
  

