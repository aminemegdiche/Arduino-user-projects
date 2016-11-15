// IR pilot control by Bartłomiej Zieliński
#include <IRremote.h>
#define irPin 11  //Odbiornik IR TSOP 2236 podłączony do pinu 11
IRrecv irrecv(irPin);
decode_results results;
 
void setup() {
   Serial.begin(9600);
   while(!Serial);
   irrecv.enableIRIn();
}
int last;
int value = 'F';
void loop() {
  
  if (Serial.available() > 0) {
   value = Serial.read();  
  }
  if (value == 'T') {
    if (irrecv.decode(&results)) {
      if(results.value != last ){
       
        last = results.value;
        Serial.print("0x");
        Serial.println(results.value, HEX);
      }
      irrecv.resume();
    }
  }
  else{
    if (irrecv.decode(&results)) {
      
      last = results.value;
      Serial.print("0x");
      Serial.println(results.value, HEX);
      
      irrecv.resume();
      delay(500);
    }
  }
}
