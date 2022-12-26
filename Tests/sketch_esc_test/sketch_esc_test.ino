#include <Servo.h>

Servo ESCfl;  // ESC-front-left
Servo ESCfr;  // ESC-front-right
Servo ESCbl;  // ESC-back-left
Servo ESCbr;  // ESC-back-right

void setup() {
  // Initialising the ESC's with low-throttle values (usually 1000*10⁻⁶s/2000*10⁻⁶s is min/max for pulse-width)
  ESCfl.attach(11, 1200, 1600); // Digital pin 11
  ESCfr.attach(10, 1200, 1600); // Digital pin 10
  ESCbr.attach(9, 1200, 1600);  // Digital pin 9 (my favourite pin)
  ESCbl.attach(6, 1200, 1600);  // Digital pin 6
}

void loop() {
  // Testing the brushless motors
  for(int i = 0; i < 3; i++){
    ESCfl.writeMicroseconds(1200 + i*100);
    ESCfr.writeMicroseconds(1200 + i*100);
    ESCbl.writeMicroseconds(1200 + i*100);
    ESCbr.writeMicroseconds(1200 + i*100);
    delay(3000);
  }
}
