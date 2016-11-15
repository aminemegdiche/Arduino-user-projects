#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN 3


LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);

int kb1 = A1;
int kb2 = A2;
int kb3 = A3;
int kb4 = A4;
char *key;
boolean stan = false;
boolean final = false;
boolean start = true;
String num1, num2;
long wynik;
char *op;
int i;

byte newChar1[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

int v1, v2, v3, v4;

void setup() {
  
  pinMode(0, INPUT_PULLUP);
  lcd.begin (20,4);
  lcd.createChar(1, newChar1);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.setCursor(1,0);
  lcd.print("Kalkulator Arduino");
  lcd.setCursor(19,0);
  lcd.write(1);
  for (i = 0;i<4; i++){
  lcd.setCursor(i,1);
  lcd.write(1);
  };
  lcd.setCursor(3,1);
  lcd.print("Zrobione przez");
  for (i = 17;i<20; i++){
  lcd.setCursor(i,1);
  lcd.write(1);
  };
  for (i = 0;i<20; i++){
  lcd.setCursor(i,2);
  lcd.write(1);
  };
  for (i = 0;i<5; i++){
  lcd.setCursor(i,3);
  lcd.write(1);
  };
  lcd.setCursor(4,3);
  lcd.print("ElektroMaras");
  for (i = 16;i<20; i++){
  lcd.setCursor(i,3);
  lcd.write(1);
  };

  delay(4000);
  lcd.clear();
  }

void loop() {
  
  v1 = analogRead(kb1);
  v2 = analogRead(kb2);
  v3 = analogRead(kb3);
  v4 = analogRead(kb4);
 
if(digitalRead(0) == LOW){
lcd.clear();
stan = false;
boolean next = false;
boolean final = false;
num1 = "";
num2 = "";
wynik = 0;
op = "";
}

if (v1 < 5 && v2 < 5 && v3 <5 && v4 < 5){
key = "nk";
};   
   
  if (v4>100 && v4<300){
  key = "=";}; //S8
  
  if (v4>300 && v4<550){
  key = "-";}; //S7
  
  if (v4>550 && v4<800){
  key = "/";}; //S6
  
  if (v4>960){
  key = "*";}; //S5
  
  if (v3>100 && v3<300){
  key = "+";}; //S4
  
  if (v3>300 && v3<550){
  key = "3";}; //S3
  
  if (v3>550 && v3<800){
  key = "6";}; //S2
  
  if (v3>960){
  key = "9";}; //S1
  
  if (v2>100 && v2<300){
  key = ".";}; //S12
  
  if (v2>300 && v2<550){
  key = "2";}; //S11
  
  if (v2>550 && v2<800){
  key = "5";}; //S10
  
  if (v2>960){
  key = "8";};//S9
  
  if (v1>100 && v1<300){
  key = "0";}; //S16
  
  if (v1>300 && v1<550){
  key = "1";}; //S15
  
  if (v1>550 && v1<800){
  key = "4";}; //S14
  
  if (v1>960){
  key = "7";}; //S13
 
  if (num1 == 0){
  lcd.setCursor(19,0);
  lcd.print("0");
  
  };

  
  if (key != "nk" && (key=="1" || key=="2" || key=="3" || key=="4" || key=="5" || key=="6" || key=="7" || key=="8" || key=="9" || key=="0" || key ==".")){
   
    if (stan != true){
      
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(20 - numLength, 0);
      lcd.print(num1);
    }
    else {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(20 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }
  
  else if (stan == false && key != "nk" && (key == "/" || key == "*" || key == "-" || key == "+")){
    if (stan == false){
      stan = true;
      op = key;
      lcd.setCursor(0,1);
      lcd.print(op);
      lcd.setCursor(0,2);
      lcd.print("--------------------");
    }
  }
 
     else if (final == true && key != "nk" && key == "="){
    if (op == "+"){
      if (num1.toInt() + num2.toInt() < num1.toInt()){
      wynik = 2147483647;}
      else{
      wynik = num1.toInt() + num2.toInt();
    }}
    else if (op == "-"){
      if (num1.toInt() - num2.toInt() > num1.toInt()){
      wynik = 2147483647;}
      else{
      wynik = num1.toInt() - num2.toInt();
    }}
    else if (op == "*"){
      if (num1.toInt() > 2147483647 / num2.toInt()){wynik = 2147483647;}else{
      wynik = num1.toInt() * num2.toInt();}
    }
    else if (op == "/"){
     if (num1.toInt() / num2.toInt() < 0){wynik = 2147483647;}else{
      wynik = num1.toInt() / num2.toInt();}
    }    
      char wynik_c[256];
      
      ltoa(wynik, wynik_c, 10);
      String wynik_s = String(wynik_c);
      int wynikl = wynik_s.length();
      if(wynik == 2147483647){
      lcd.setCursor(15,3);
      lcd.print("ERROR");
      }else{
      lcd.setCursor(20-wynikl,3);
      
      lcd.print(wynik);
      lcd.setCursor(0,3);
      lcd.print("=");
  };
      
  
  };
  
  
delay(220);}

