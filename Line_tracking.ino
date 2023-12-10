void forward(int x){

    digitalWrite(7, 1);
    analogWrite(5, x);
    digitalWrite(8, 1);
    analogWrite(6, x);
}
void backwards(int x){

    digitalWrite(7, 0);
    analogWrite(5, x);
    digitalWrite(8, 0);
    analogWrite(6, x);
}
void left(int x){

    digitalWrite(7, 1);
    analogWrite(5, x);
    digitalWrite(8, 0);
    analogWrite(6, x);
}
void right(int x){

    digitalWrite(7, 0);
    analogWrite(5, x);
    digitalWrite(8, 1);
    analogWrite(6, x);
}
void leftforward(int x){

    digitalWrite(7, 1);
    analogWrite(5, x);
    digitalWrite(8, 1);
    analogWrite(6, x/2);
}
void rightforward(int x){

    digitalWrite(7, 1);
    analogWrite(5, (x/2));
    digitalWrite(8, 1);
    analogWrite(6, x);
}
void leftbackward(int x){

    digitalWrite(7, 0);
    analogWrite(5, x);
    digitalWrite(8, 0);
    analogWrite(6, x/2);
}
void rightbackward(int x){

    digitalWrite(7, 0);
    analogWrite(5, x/2);
    digitalWrite(8, 0);
    analogWrite(6, x);
}
void stopit(){

    digitalWrite(7, 0);
    analogWrite(5, 0);
    digitalWrite(8, 0);
    analogWrite(6, 0);
}

int Rsens = A0;
int Msens = A1;
int Lsens = A2;

void setup() {
  // put your setup code here, to run once:
    pinMode(5, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(3, OUTPUT);
      digitalWrite(3, 1);
    pinMode(Rsens, INPUT);
    pinMode(Msens, INPUT);
    pinMode(Lsens, INPUT);

    Serial.begin(9600);

}
void loop(){

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


