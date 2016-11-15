#include <VirtualWire.h>
int guzik=4;
void setup()
{
  pinMode(guzik, INPUT_PULLUP); 
  vw_set_tx_pin(9);
    vw_setup(2000);	 // Bits per sec
}

void loop()
{
  char *msg;
    
if (digitalRead (guzik)==LOW) {msg="on"; }
else {msg="off"; } ;

      vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    delay(200);
}
