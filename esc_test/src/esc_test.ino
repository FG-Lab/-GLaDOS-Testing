#include <Arduino.h>
#include <Servo.h>

Servo ESC;

void setup() {
  Serial.begin(9600);
  ESC.attach(9, 0, 60);
  ESC.write(0);
  delay(2000);
}


double currentSpeed = 0;
double newSpeed;

void loop() {
  newSpeed = map(analogRead(0), 0, 1023, 0, 60);
  if(newSpeed - currentSpeed > 3){
    Serial.println("Jump too big!");
    currentSpeed = currentSpeed + 0.6;
  } else{
    currentSpeed = newSpeed;
  }
  ESC.write(currentSpeed);
  Serial.print((currentSpeed / 60) * 100);
  Serial.println("%");
}
