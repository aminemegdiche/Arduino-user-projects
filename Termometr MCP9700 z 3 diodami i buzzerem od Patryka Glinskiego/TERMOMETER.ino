//do pinu A0 podłączamy nóżkę z danymi w czujniku teperatury mcp9700 u mnie jest to środkowa
//lewa to napięcie 5v LUB 3.3v
//prawa masa
//każdy musi sobie sprawdzic jak to jest w jego czujniku.
// pin 8 buzzer z generatorem
//do pinu 13 podłączamy diode która bedzie mrugała jak jest wiecej niż 27.15 stopni fajnie jak by była czerwona bedzie to ładniej wyglądać.
//do pinu 12 podłaczamy diode zielona która bedzie mrugać jak bedzie normalnie czyli mniej niż 27.15 stopni
//do pinu 11 podłączamy diode niebieską która bedzie mrugac jak bedzie zimno czyli mniej niż 10 stopni
// oczywiście wszystkie diody podłączamy oprucz tych pinów do masy i od pinów 13,12,11 za pomoca rezystorów 220 Omów
//w programie można odczytac teperature wysyłana przez czujnik za pomoca monitora portu szeregowego.
//program można samemu wyedytować np. żeby dioda czerwona świeciła gdy bendze więciej niż 39 stopni
// komenda if(temp > 27.15) ozmacza gdy teperatura bedzie wieksza niż 27.15 stopni zrób to i to pisze sie to pod spodem w mym projekcie jest to mruganie dioda 






float temp;
void setup() {
  pinMode(11,OUTPUT);      
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(8,OUTPUT); //można usunąć pin 8 bo ja to zrobiłem jakby ktoś chciał brzęczyk dodatkowo gdy świeci dioda czerwona
  Serial.begin(9600);
  //piny wejscia i szybkośći 
  
   
};

void loop () {
  if(temp > 27.15)   //ustawienie diody czerwonej
  digitalWrite(13,HIGH);  //włączenie napięcia na pinie 13
  delay(150); //opuźnienie czasowe
  digitalWrite(13,LOW);  //wyłączenie napięcia
  
  if(temp < 27.15) //ustawienie diody zielonej
  digitalWrite(12,HIGH); //włączenie napięcia na pinie 12
  delay(150); //opuźnienie czasowe
  digitalWrite(12,LOW); //wyłączenie napięcia
  
  if(temp < 10.15) //ustawienie diody niebieskiej
  digitalWrite(11,HIGH); //włączenie napięcia na pinie 11
  delay(150); //opóźnienie czasowe
  digitalWrite(11,LOW);  //wyłączenie napięcia 
  
  if(temp > 27.15)
  digitalWrite(8,HIGH);       //Ustawienie brzęczyka
  delay(150);
  digitalWrite(8,LOW);
   
  
  temp = analogRead(0)*5/1024.0;
  temp = temp - 0.5;             //komendy dzieki którym arduino przelicza dane z czujnika teperatury na stopnie 
  temp = temp / 0.01;
  
  Serial.println(temp);
  delay(900);
  
}
//mam nadzieje że projekt sie spodoba jest on dosyć prosty a zrobiłem go z myśla dla osób które nie maja wyświetlacza a chciały by zobaczyć jakoś swoje dane.
//Wykonał PPTG

