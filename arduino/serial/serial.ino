#include <SoftwareSerial.h>
#include <stdio.h>

//#define DEBGUG_KPH
#define DEBUG_BLINKER

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  static int kph = 0;
  static int blk = 0;
  char buffer[50];
  // put your main code here, to run repeatedly:
  while(1)
  {
#ifdef DEBUG_KPH
    sprintf(buffer, "kph %d\r\n", kph);
    (void)Serial.write(buffer);
    kph += 1;
    if(kph == 220)
      kph = 0;
#endif
#ifdef DEBUG_BLINKER
    sprintf(buffer, "blk %d\r\n", blk);
    (void)Serial.write(buffer);
    blk += 1;
    if(blk == 3)
      blk = 0;
#endif
    delay(1000);
  } 
}
