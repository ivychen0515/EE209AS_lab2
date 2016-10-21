#include"Servo.h"

#define LEFT 13           //D7
#define RIGHT 12          //D6
#define MANUAL 14      //D5

#define PHOTO_R A0
#define SERVO 5
#define BUTTON 4

const short int LED_2 = 2;

uint8_t LStatus = LOW;
uint8_t RStatus = LOW;
uint8_t ManualMode = LOW;

int ini_light_val = 0;
int curr_light_val = 0;
int rotatePause = 200;

uint8_t hitConfirm = 0;

Servo myServo;

//BUILTIN_LED is 16

void setup() {
  //Inputs
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(MANUAL, INPUT);

  pinMode(PHOTO_R, INPUT);
  pinMode(BUTTON, INPUT);

  //Outputs
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LED_2, OUTPUT);

  //Initialization
  myServo.attach(SERVO);
  servoReset();
  setLED();

  //Interrupts
  attachInterrupt(LEFT, LHighInterrupt, RISING);
  attachInterrupt(RIGHT, RHighInterrupt, RISING);
  attachInterrupt(MANUAL, MHighInterrupt, RISING);
  Serial.begin(9600);
}

//Movement for servo
void servoReset() {
  myServo.write(90);
}

void servo_hit_right() {
  myServo.write(135);
  delay(rotatePause);
  servoReset();
}

void servo_hit_left() {
  myServo.write(45);
  delay(rotatePause);
  servoReset();
}

//Interrupt for left hit
void LHighInterrupt() {     //this function get called when the Left signal Low->High
  LStatus = HIGH;//turn led ON
  Serial.println("LPin is now High!!!");
  detachInterrupt(LEFT);
  attachInterrupt(LEFT, LLowInterrupt, FALLING);
  hitConfirm = 0;
}

void LLowInterrupt() {
  LStatus = LOW;//turn led OFF
  Serial.println("LPin is now Low!!!");
  detachInterrupt(LEFT);
  attachInterrupt(LEFT, LHighInterrupt, RISING);
}

//Interrupt for right hit
void RHighInterrupt() {     //this function get called when the Right signal Low->High
  RStatus = HIGH;//turn led ON
  Serial.println("RPin is now High!!!");
  detachInterrupt(RIGHT);
  attachInterrupt(RIGHT, RLowInterrupt, FALLING);
  hitConfirm = 0;
}

void RLowInterrupt() {
  RStatus = LOW;//turn led OFF
  Serial.println("RPin is now Low!!!");
  detachInterrupt(RIGHT);
  attachInterrupt(RIGHT, RHighInterrupt, RISING);
}

//Interrupt for Manual Mode
void MHighInterrupt() {     //this function get called when the Manuel signal Low->High
  ManualMode = LOW;//turn led ON
  Serial.println("MPin is now High!!!");
  detachInterrupt(MANUAL);
  attachInterrupt(MANUAL, MLowInterrupt, FALLING);
}

void MLowInterrupt() {
  ManualMode = HIGH;//turn led OFF
  Serial.println("MPin is now Low!!!");
  detachInterrupt(MANUAL);
  attachInterrupt(MANUAL, MHighInterrupt, RISING);
}
void manualServo() {
  if (ini_light_val == 0) {
    ini_light_val = curr_light_val;
  }

  else if (curr_light_val < 0.8 * ini_light_val) {
    servo_hit_right();
  }

  if (digitalRead(BUTTON)) {
    servo_hit_left();
  }
}


void setLED() {
  digitalWrite(LED_2, HIGH - LStatus);
  digitalWrite(BUILTIN_LED, HIGH - RStatus);
}

void loop() {
  //Status data updated from Photoresistor
  curr_light_val = analogRead(PHOTO_R);

  setLED();
  if (ManualMode == HIGH) {
    manualServo();
  }
  else if (hitConfirm == 0) {
    if (LStatus == HIGH) {
      servo_hit_left();
      hitConfirm = 1;
    }
    else if (RStatus == HIGH) {
      servo_hit_right();
      hitConfirm = 1;
    }
  }
}
