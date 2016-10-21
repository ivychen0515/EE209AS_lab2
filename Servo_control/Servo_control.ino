#include"Servo.h"

#define PHOTO_R A0
#define SERVO 5
#define BUTTON 4

int ini_light_val = 0;
int curr_light_val = 0;
int rotatePause = 200;

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  pinMode(PHOTO_R, INPUT);
  pinMode(BUTTON, INPUT);
  
  myservo.attach(SERVO);
  servoReset();

  Serial.begin(9600);
}

void servoReset(){
  myservo.write(90);
}

void servo_hit_right(){
  myservo.write(135);
  delay(rotatePause);
  servoReset();
}

void servo_hit_left(){
  myservo.write(45);
  delay(rotatePause);
  servoReset();
}

void loop() {
  // put your main code here, to run repeatedly:
  curr_light_val = analogRead(PHOTO_R);
  
  if (ini_light_val == 0)
    ini_light_val = curr_light_val;

  else if (curr_light_val < 0.8*ini_light_val){
    servo_hit_right();
  }

  if (digitalRead(BUTTON)){
    servo_hit_left();
  }
  Serial.println(analogRead(PHOTO_R));
}
