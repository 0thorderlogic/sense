#include <Servo.h>


Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;

int angle = 90;  // Default position at 90 degrees

void setup() {
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s4.attach(5);
  s5.attach(6);
  s6.attach(7);

  s1.write(angle);  
  s2.write(angle);  
  s3.write(angle);  
  s4.write(angle);  
  s5.write(angle);  
  s6.write(angle);  
  
  Serial.begin(9600);
  Serial.println("Enter angle (0 to 180):");
}

void loop() {
  if (Serial.available()) {
    int input = Serial.parseInt();  // Read integer from serial

    if (input >= 0 && input <= 360) {
      angle = input;    
           // Update stored angle
        s1.write(angle);  
        s2.write(angle);  
        s3.write(angle);  
        s4.write(angle);  
        s5.write(angle);  
        s6.write(angle);  
        
      Serial.print("Moved to: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid angle! Must be between 0–180.");
    }

    // Clear Serial buffer
    while (Serial.available()) Serial.read();

    Serial.println("Enter next angle:");
  }
}
