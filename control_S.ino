//Arduino Sketch for Team B
#include <Servo.h>

int buffer[4]; //0~3 - motor

void setup() {

  for(int i = 2; i <= 10; i++) {
     pinMode(i, OUTPUT); 
  }

  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 4) { //gather 5 bits in hardware buffer
        Serial.println("got 4 bits");
        byte message = Serial.read();

        if (message == 'S') { //Throttle message starts with T followed by 8 Hexadecimal inputs
                
                for(int i=0; i < 4; i++) {
                  buffer[i] = charToInt(Serial.read());
                  Serial.println(i + "" + buffer[i]);
                }
                
                for(int i=0; i < 4; i++) {
                  writeMotor( 2*(i+1), buffer[i] );  
                }
                               
        }

  }
}

int charToInt(char c) {
    return (int)c-48;
}

void writeMotor(int mchannel1, int polarity) { //O - Short with Neg, 1 - Positive, 2 - Negative, 3 - Short with Pos
    switch (polarity) {
      case 1:
         digitalWrite(mchannel1, LOW);
         digitalWrite(mchannel1+1, LOW);
         Serial.println("0");
         delay(1);
         break;
      case 0:
         digitalWrite(mchannel1, HIGH);
         digitalWrite(mchannel1+1, LOW);
         Serial.println("+");
         delay(1);
         break;
      case 2:
         digitalWrite(mchannel1, LOW);
         digitalWrite(mchannel1+1, HIGH);
         Serial.println("-");
         delay(1);
         break;
      case 3:
         digitalWrite(mchannel1, HIGH);
         digitalWrite(mchannel1+1, HIGH);
         Serial.println("0");
         delay(1);
         break;
    }
    delay(1);
}
