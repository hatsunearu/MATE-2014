//Arduino Motor Controller code for Team A

#include <Servo.h>

int buffer[7]; //0~4 - Motor, 5: claw, 6: rotate
Servo s_rotate;
Servo s_claw;

void setup() {

  for(int i = 2; i <= 10; i++) {
     pinMode(i, OUTPUT); 
  }
  s_rotate.attach(11);
  s_claw.attach(12);
 
  s_rotate.write(90);
  s_claw.write(180);

  Serial.begin(9600);
} 

void loop() {
  while(Serial.available() > 7) { //gather 9 bits in hardware buffer
     
        byte message = Serial.read();

        if (message == 'K') { //Throttle message starts with T followed by 8 Hexadecimal inputs
                
                for(int i=0; i < 7; i++) {
                  buffer[i] = charToInt(Serial.read());
                }
                
                for(int i=0; i < 5; i++) {
                  writeMotor( 2*(i+1), buffer[i] );  
                }
                
                switch (buffer[5]) {
                  case 0:
                    break;
                  case 1:
                    s_claw.write(s_claw.read() + 1);
                    Serial.println("Claw +1");
                    break;
                  case 2:
                    s_claw.write(s_claw.read() - 1);
                    Serial.println("Claw -1");
                    break;
                }
                
                switch (buffer[6]) {
                  case 0:
                    brea                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         k;
                  case 1:
                    s_claw.write(180);
                    Serial.println("Claw pos1");
                    break;
                  case 2:
                    s_claw.write(90);
                    Serial.println("Claw pos2");
                    break;
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
         Serial.println(mchannel1 + " Short-");
         break;
      case 0:
         digitalWrite(mchannel1, HIGH);
         digitalWrite(mchannel1+1, LOW);
         Serial.println(mchannel1 + " +");
         break;
      case 2:
         digitalWrite(mchannel1, LOW);
         digitalWrite(mchannel1+1, HIGH);
         Serial.println(mchannel1 + " -");
         break;
      case 3:
         digitalWrite(mchannel1, HIGH);
         digitalWrite(mchannel1+1, HIGH);
         Serial.println(mchannel1 + " Short+");
         break;
    }
    delay(1);
}
