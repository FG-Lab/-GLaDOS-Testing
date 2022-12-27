#include <Servo.h>

Servo ESCfl;  // ESC-front-left
Servo ESCfr;  // ESC-front-right
Servo ESCbl;  // ESC-back-left
Servo ESCbr;  // ESC-back-right

unsigned long time; // Used for testing-purposes

void setup() {
  Serial.begin(9600);
  // Initialising the ESC's with low-throttle values (usually 1000*10⁻⁶s/2000*10⁻⁶s is min/max for pulse-width)
  ESCfl.attach(11, 1200, 1600); // Digital pin 11
  ESCfr.attach(10, 1200, 1600); // Digital pin 10
  ESCbr.attach(9, 1200, 1600);  // Digital pin 9 (my favourite pin)
  ESCbl.attach(6, 1200, 1600);  // Digital pin 6

  time = micros();
}
int i;
void loop() {
  // Testing the brushless motors
  i = (micros() - time) / 100000;
  if(i > 350){
    time = micros();
  }
  ESCfl.writeMicroseconds(1200 + i);
  ESCfr.writeMicroseconds(1200 + i);
  ESCbl.writeMicroseconds(1200 + i);
  ESCbr.writeMicroseconds(1200 + i);
  Serial.println(i);
}
