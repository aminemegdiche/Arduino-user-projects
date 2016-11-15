void setup(){
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  serial.begin(9600);
  }
  
int czujnik;
boolean stan = false;

void loop(){

 czunik = analogRead(A0) * 5 / 1023;
 Serial.println("czujnik: " + String(czujnik));
 if(czujnik < 4){
 stan = true;
 }
 
 if(stan == true){
  digitalWrite(8, HIGH);
  int licznik = 0;
  
  for (int i = 0; i<11; i++){
  delay(1000);
  int teltest = analogRead(A0) * 5 / 1023;
  if (teltest >=4){
  licznik = licznik + 1;
  }
  if(licznik > 4){
  stan = false;
  }
  
  }
  
  }
  if (stan == false){
  digitalWrite(8, LOW);
   
  }
  delay(200);
  }