#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>

#define ESC1_PIN 11
#define ESC2_PIN 10
#define ESC3_PIN 9
#define ESC4_PIN 6

// Input used for calibrating the motors
char input;

// The Electronic Speed Controllers
Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

// Max-values for the motors speed
int max_1 = 0;
int max_2 = 0;
int max_3 = 0;
int max_4 = 0;

void setup() {
	Serial.begin(9600); 
	ESC1.attach(ESC1_PIN, 0, 180);
  ESC2.attach(ESC2_PIN, 0, 180);
  ESC3.attach(ESC3_PIN, 0, 180);
  ESC4.attach(ESC4_PIN, 0, 180);
}

void loop() {
	if(Serial.available()){
		input_active(Serial.read());
    Serial.print("Speed 1: ");
    Serial.println(max_1);
    Serial.print("Speed 2: ");
    Serial.println(max_2);
    Serial.print("Speed 3: ");
    Serial.println(max_3);
    Serial.print("Speed 4: ");
    Serial.println(max_4);
    Serial.println();
    Serial.println("//////////////");
    Serial.println();
	}
  ESC1.write(max_1);
  ESC2.write(max_2);
  ESC3.write(max_3);
  ESC4.write(max_4);
}

void input_active(char i){
  if(i == '1'){
    if(max_1 < 180){
      max_1++;
    }
  }
  if(i == 'q'){
    if(max_1 > 0){
      max_1--;
    }
  }
  if(i == '2'){
    if(max_2 < 180){
      max_2++;
    }
  }
  if(i == 'w'){
    if(max_2 > 0){
      max_2--;
    }
  }
  if(i == '3'){
    if(max_3 < 180){
      max_3++;
    }
  }
  if(i == 'e'){
    if(max_3 > 0){
      max_3--;
    }
  }
  if(i == '4'){
    if(max_4 < 180){
      max_4++;
    }
  }
  if(i == 'r'){
    if(max_4 > 0){
      max_4--;
    }
  }
}

/*
void accelerate(Servo ESC, int& currentSpeed, int){
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
}
*/

/*
Servo ESC;
int maxSpeed;

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
*/