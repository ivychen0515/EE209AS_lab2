#include <Servo.h>
const short int BUILTIN_LED1 = 2; //GPIO2
const short int BUILTIN_LED2 = 16;//GPIO16
Servo myServo;
short int pos;
short int low = 15;
short int high = 160;
void setup() {

pinMode(BUILTIN_LED1, OUTPUT); // Initialize the BUILTIN_LED1 pin as an output 
pinMode(BUILTIN_LED2, OUTPUT); // Initialize the BUILTIN_LED2 pin as an output
myServo.attach(5);
}

void loop() {

digitalWrite(BUILTIN_LED1, LOW); // Turn the LED ON by making the voltage LOW 
digitalWrite(BUILTIN_LED2, HIGH); // Turn the LED off by making the voltage HIGH 
//delay(1000); // Wait for a second 


for (pos = low; pos <= high; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  delay(100);
  for (pos = high; pos >= low; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  
digitalWrite(BUILTIN_LED1, HIGH); // Turn the LED off by making the voltage HIGH 
digitalWrite(BUILTIN_LED2, LOW); // Turn the LED ON by making the voltage LOW 

  myServo.write(90);
  delay(1000);
  myServo.write(low);
  delay(500);
}
