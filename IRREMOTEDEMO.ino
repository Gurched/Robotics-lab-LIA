#include <IRremote.h>   // include the library for the IR remote


#define IR_RECEIVE_PIN 9    // set the receiever pin for the receiver as pin 9

int command;        // set command as an interger
int speed = 0;      // give 0 as the initial speed
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

void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);    // set the receiver pin as a reciever

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
 
if (IrReceiver.decode()) {      // when the pin receieves a code (when you press a button on the ir)

    command = IrReceiver.decodedIRData.command;         // give an interger for command to decode the buttons when pressed
    Serial.println(command);    // this will print the value of the data
    delay(100);                 // adding a pause to the program to read the data
    IrReceiver.resume();        // Resume the ir reciever to recieve
}
if(command == 69){   /*button up*/
  forward(speed);   // go forwards
    }
if(command == 70){   /*button down*/
  backwards(speed);   // go backwards
    }
if(command == 71){    /*button left*/
  left(speed);    // go left
    }
if(command == 72){   /*button right*/
  right(speed);   // go right
    }
if(command == 27){   /*button top-right*/
  rightforward(speed);    // go right forwards
}
if(command == 73){    /*button top-left*/
  leftforward(speed);   // go left forwards
}
if(command == 74){    /*button bottom-left*/
  leftbackward(speed);    // go left backwards
}
if(command == 28){    /*button bottom-right*/
  rightbackward(speed);   // go right backwards
}
if(command == 68){    /*button play-pause*/
  stopit();    // stop
}
if(command == 2){   /*button volume up*/
  speed = speed + 25;   // plus 25 speed
  command = 0;    // return command back to 0 so the program doesn't repeat
}
if(command == 3){   /*button volume down*/
  speed = speed - 25;   // minus 25 speed
  command = 0;    // return command back to 0 so the program doesn't repeat
}
if(command == 17){    /*button 1*/

  int Rval = analogRead(Rsens);   // read the right sensor
  int Mval = analogRead(Msens);   // read the middle sensor
  int Lval = analogRead(Lsens);   // read the left sensor

if (Mval >= 900 && Rval >= 900 && Lval >= 900){   // if all the sensors are not receiving light

  stopit();    // stop the car

} else if (Mval >= 500 && Mval <= 900){   // if the middle sensor is scanning a black line

  forward(100);   // go forwards


} else if (Mval <= 500){    // if the middle is not scanning the line/scanning the ground
    if (Rval >= 400 && Lval <= 400) {   // check if the right sensor scans the black line
    right(100);   // go right

  } 
    else if (Lval >= 400 && Rval <= 400) {    // check if the left sensor scans the black line
      left(100);    // go left
  } 
    else if (Mval <=500 && Lval <= 500 && Rval <= 500) {    // if none of the sensors can find anything, search for the line
      right(100);   // keeps on turning right
    }
}
delay(50);    // use a delay so that the motor can actually move
stopit();    // stop the car
delay(1);     // use a delay to stop it for a second
  }
}