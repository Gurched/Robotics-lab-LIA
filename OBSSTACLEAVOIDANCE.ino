#include <Servo.h>    // include the library for the servo motor
Servo myservo;    // give and object to call the servo

float duration, distance;   // float so we can have decimal numbers

int trigPin = 13;   // give the trigger pin and interger
int echoPin = 12;   // give the echo pin an interger

int Rsens = A0;     // give the right sensor pin an interger
int Msens = A1;     // give the middle sensor pin an interger
int Lsens = A2;     // give the left sensor pin an interger

void forward(int x){        // goes forward

    digitalWrite(7, 1);     //right motor (same direction as left)
    analogWrite(5, x);      //speed for left motor
    digitalWrite(8, 1);     //left motor (same direction as right)
    analogWrite(6, x);      //speed for rightr motor
}
void backwards(int x){      // goes backwards

    digitalWrite(7, 0);     //right motor goes back
    analogWrite(5, x);      
    digitalWrite(8, 0);     //left motor goes back
    analogWrite(6, x);
}
void left(int x){           // goes left

    digitalWrite(7, 1);     //right motor is forward
    analogWrite(5, x);
    digitalWrite(8, 0);     //left motor is backwards
    analogWrite(6, x);
}
void right(int x){          // goes right

    digitalWrite(7, 0);     //right motor is backwards
    analogWrite(5, x);
    digitalWrite(8, 1);     //left motor is forwards
    analogWrite(6, x);
}
void leftforward(int x){    // goes left and forwards

    digitalWrite(7, 1);     //right motor is forwards
    analogWrite(5, x);      // speed is regular
    digitalWrite(8, 1);     //left motor is forwards
    analogWrite(6, x/2);    // speed is halfed
}
void rightforward(int x){   // goes right and forwards

    digitalWrite(7, 1);     //right motor is forwards
    analogWrite(5, (x/2));  // speed is halfed
    digitalWrite(8, 1);     //left motor is forwards
    analogWrite(6, x);      // speed is regular
}
void leftbackward(int x){   // left and backwards

    digitalWrite(7, 0);     //right motor is backwards
    analogWrite(5, x);      // speed is regular
    digitalWrite(8, 0);     //left motor is backwards
    analogWrite(6, x/2);    // speed is halfed
}
void rightbackward(int x){  // right and backwards

    digitalWrite(7, 0);     //right motor is backwards
    analogWrite(5, x/2);    // speed is halfed
    digitalWrite(8, 0);     //left motor is backwards
    analogWrite(6, x);      // speed regular
}
void stopit(){              //stop

    digitalWrite(7, 0);     //right motor is off
    analogWrite(5, 0);      // speed is off
    digitalWrite(8, 0);     //left motor is off
    analogWrite(6, 0);      // speed is off
}
void checkdist(){   //Create a function for checking the distance

  digitalWrite(trigPin, LOW);   //turn off the trigger pin
  delayMicroseconds(2);   //give it a delay
  digitalWrite(trigPin, HIGH);    //pulse the trigger pin
  delayMicroseconds(20);    //give it a longer delay
  digitalWrite(trigPin, LOW);   //turn off the trigger pin
  duration = pulseIn(echoPin, HIGH);    //read the pulses of the trigger pin
  distance = (duration / 58);   //this will take the time it takes to pulse and speed of sound to convert to cm.
  return (int)distance;   //this will turn the distance from float to int
}

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);     // turn on speed control for the right motor
  pinMode(8, OUTPUT);     // turn on the right motor
  pinMode(6, OUTPUT);     // turn on speed control for the left motor
  pinMode(7, OUTPUT);     // turn on the left motor
  pinMode(3, OUTPUT);     // this enables the motor to receive
    digitalWrite(3, 1);   // this needs to be on to start the motors

  pinMode(Rsens, INPUT);  // check the right sensor for line tracking
  pinMode(Msens, INPUT);  // check the middle sensor for line tracking
  pinMode(Lsens, INPUT);  // check the left sensor for line tracking

  pinMode(trigPin, OUTPUT);   // set trigger pin as an output
  pinMode(echoPin, INPUT);    // set echo pin as an input

  myservo.attach(10);         // attach the servo pin to pin 10

  Serial.begin(9600);         //intialize the serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  int Rval = analogRead(Rsens);   // read the right sensor
  int Mval = analogRead(Msens);   // read the middle sensor
  int Lval = analogRead(Lsens);   // read the left sensor
  
if (Mval >= 900 && Rval >= 900 && Lval >= 900){   // if all the sensors are not receiving light

  stopit();    // stop the car

} else {
  checkdist();    // check the distance

  if (distance <= 25){    // if the distance is smaller than 25

  stopit();   // stop the car

  myservo.write(10);    // look right
  delay (1000);   // stop for a second
  checkdist();    // check distance again
    if (distance <= 25){    // if the distance on the right is smaller than 25
  
    myservo.write(170);   // look left
    delay(1000);          // stop for a second
    checkdist();          // check distance again

    if (distance <= 25){    // if the distance on the left is smaller than 25

      myservo.write(90);    // look forwards

      backwards(100);       //go back
      delay(1000);          // stop the program for a second
      left(100);            // turn left
      delay(1300);          // turn left for 90 degrees
      stopit();             // stop the car
      delay(500);           // paur for half a second

    } else{                 // since the distance on the left is bigger than 25

      myservo.write(90);    // look forwards

      delay(100);           // stop for 1/10 of a second
      left(100);            // turn left
      delay(650);           // turns until 90 degrees
      stopit();             // stops the momentum
      delay(500);           // pause the program

    }
    } else {                //  since the distance on the right is bigger than 25

      myservo.write(90);    // look forwards

      delay(100);           // stop for 1/10 of a second
      right(100);           // turn right
      delay(650);           // turns until 90 degrees
      stopit();             // stops the momentum
      delay(500);           // pause the program
    }
  } else {                  // since the distance infront is bigger than 25
forward(100);               // go forwards
  }
}
}



