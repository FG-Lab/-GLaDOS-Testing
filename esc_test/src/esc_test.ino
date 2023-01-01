#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>

Servo ESC;
int maxSpeed = 0;

void setup() {
  Serial.begin(9600);
  ESC.attach(9, 0, 60);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);

  maxSpeed = EEPROM.read(0);
}


double currentSpeed = 0;
double newSpeed;

void loop() {
  if(digitalRead(2)){
    maxSpeed = esc_calibration();
  } 

  newSpeed = map(analogRead(0), 0, 1023, 0, maxSpeed);
  if(newSpeed - currentSpeed > 1){
    Serial.println("Jump too big!");
    currentSpeed += 0.5;
  } else{
      if(currentSpeed - newSpeed > 1){
        Serial.println("Jump too big!");
        currentSpeed -= 0.5;
      } else{
        currentSpeed = newSpeed;
      }
  }
 
  ESC.write(currentSpeed);
  Serial.print((currentSpeed / 180) * 100);
  Serial.println("%");
}

int esc_calibration(){
  // Test-sequence SETUP
  int maxSpeed = 0;
  long time = millis();
  delay(1000);

  // Test-sequence START
  digitalWrite(13, HIGH);
  while(!digitalRead(2) & maxSpeed < 180){
    ESC.write(maxSpeed);
    if(millis() - time > 250){
      maxSpeed += 1;
      Serial.println(maxSpeed);
      time = millis();
    }
  }

  // Test-sequence SHUTDOWN
  digitalWrite(13, LOW);
  delay(2500);
  if(maxSpeed-4 >= 0){
    EEPROM.write(0, maxSpeed-8);
    return maxSpeed-8;
  }
  return maxSpeed;
}