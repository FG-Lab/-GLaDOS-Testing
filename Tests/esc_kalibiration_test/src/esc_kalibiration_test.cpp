// Dies ist ein Test für die ESC-Kalibiration. Funktioniert vermutlich nicht?
// Die ESC's sollten alle in den ersten paar Sekunden piepen, einige Sekunde später
// dann wieder. Zeit könnte abweichen.
#include <Arduino.h>
#include <Servo.h>

Servo ESCfl;  // ESC-front-left
Servo ESCfr;  // ESC-front-right
Servo ESCbl;  // ESC-back-left
Servo ESCbr;  // ESC-back-right

unsigned long time; // Used for testing-purposes

void setup() {
  Serial.begin(9600);
  // Initialising the ESC's with full-range-throttle values (usually 1000*10⁻⁶s/2000*10⁻⁶s is min/max for pulse-width)
  ESCfl.attach(11, 1000, 2000); // Digital pin 11
  ESCfr.attach(10, 1000, 2000); // Digital pin 10
  ESCbr.attach(9, 1000, 2000);  // Digital pin 9 (my favourite pin)
  ESCbl.attach(6, 1000, 2000);  // Digital pin 6

  time = micros();
}
int i;
void loop() {
  while(micros() - time < 6500000){
    // Setting the max value for ESC, ESC should make noises
    Serial.println("Setting max value - Still in Progress");
    ESCfl.writeMicroseconds(2000);
    ESCfr.writeMicroseconds(2000);
    ESCbl.writeMicroseconds(2000);
    ESCbr.writeMicroseconds(2000);
  }
  time = micros();
  while(micros() - time < 6500000){
    // Setting the min value for ESC, ESC should make noises
    Serial.println("Setting min value - Still in Progress");
    ESCfl.writeMicroseconds(1000);
    ESCfr.writeMicroseconds(1000);
    ESCbl.writeMicroseconds(1000);
    ESCbr.writeMicroseconds(1000);
  }

  // Testing the brushless motors
  time = micros();
  while(1){
    i = (micros() - time) / 25000;
    if(i > 995){
      time = micros();
    } 
    ESCfl.writeMicroseconds(1000 + i);
    ESCfr.writeMicroseconds(1000 + i);
    ESCbl.writeMicroseconds(1000 + i);
    ESCbr.writeMicroseconds(1000 + i);
    Serial.print("Ongoin test-sequence: Current speed is ");
    Serial.print((1000+i));
    Serial.println("/2000");
  }
}

