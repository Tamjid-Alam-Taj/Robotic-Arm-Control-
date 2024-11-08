#include <Servo.h>

// Servo motor declarations for the robotic arm
Servo s1;    // Servo 1
Servo s2; // Servo 2
Servo s3;    // Servo 3
Servo s4;     // Servo 4
Servo s5;    // Servo 5
Servo s6;  // Servo 6

int servo1 = 90;
int servo2 = 110;
int servo3 = 40;
int servo4 = 50;
int servo5 = 90;
int servo6 = 90;

int bt_data;

// Motor driver pins connected to Arduino
int IN1 = 7;  // Left motor forward
int IN2 = 6;  // Left motor backward
int IN3 = 5;  // Right motor forward
int IN4 = 4;  // Right motor backward

// BUK Transistor pin to control power to the motor driver
int bukPower = 8; // Pin 8 controls the BUK transistor

char command;

void setup() {
  Serial.begin(9600);  // Set the baud rate to your Bluetooth module.

  // Motor control pin setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // BUK transistor setup
  pinMode(bukPower, OUTPUT);
  
  // Turn on the BUK transistor to provide power to the motor driver
  digitalWrite(bukPower, HIGH);  // Enable motor power

  // Servo motor pin assignments
  s1.attach(8); //base    
  s2.attach(9);  
  s3.attach(10);    
  s4.attach(11);     
  s5.attach(12);    
  s6.attach(13); // gripper

  
  s1.write(servo1); 
  s2.write(servo2); 
  s3.write(servo3); 
  s4.write(servo4);
  s5.write(servo5);
  s6.write(servo6);

  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read(); 
    stopCar(); // Initialize with motors stopped

    // Control Car Movement
    switch (command) {
      case 'F':  
        moveForward();
        break;
      case 'B':  
        moveBackward();
        break;
      case 'L':  
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      
      // Arm Movement Control
      case 'Z':
        if (servo1 < 180) servo1=+5; // Waist move right
        s1.write(servo1);
        break;
      case 'z':
        if (servo1 > 0) servo1-=5; // Waist move left
        s1.write(servo1);
        break;
      case 'A':
        if (servo2 > 0) servo2-=5; // Shoulder down
        s2.write(servo2);
        break;
      case 'b':
        if (servo2 < 180) servo2+=5; // Shoulder up
        s2.write(servo2);
        break;
      case 'C':
        if (servo3 > 0) servo3-=5; // Elbow down
        s3.write(servo3);
        break;
      case 'D':
        if (servo3 < 180) servo3+=5; // Elbow up
        s3.write(servo3);
        break;
      case 'E':
        if (servo4 < 180) servo4+=5; // Wrist roll clockwise
        s4.write(servo4);
        break;
      case 'f':
        if (servo4 > 0) servo4-=5; // Wrist roll counter-clockwise
        s4.write(servo4);
        break;
      case 'G':
        if (servo5 < 180) servo5+=5; // Wrist pitch up
        s5.write(servo5);
        break;
      case 'H':
        if (servo5 > 0) servo5-=5; // Wrist pitch down
        s5.write(servo5);
        break;
      case 'I':
        if (servo6 < 180) servo6+=5; // Gripper open
        s6.write(servo6);
        break;
      case 'J':
        if (servo6 > 0) servo6-=5; // Gripper close
        s6.write(servo6);
        break;
      default:
        stopCar(); // Stop the car if an invalid command is received
    }
  }
}

// Move the car forward (adjusted logic)
void moveForward() {
  digitalWrite(IN1, LOW);   // Left motor forward off
  digitalWrite(IN2, HIGH);  // Left motor backward
  digitalWrite(IN3, LOW);   // Right motor forward off
  digitalWrite(IN4, HIGH);  // Right motor backward
}

// Move the car backward (adjusted logic)
void moveBackward() {
  digitalWrite(IN1, HIGH);  // Left motor forward
  digitalWrite(IN2, LOW);   // Left motor backward off
  digitalWrite(IN3, HIGH);  // Right motor forward
  digitalWrite(IN4, LOW);   // Right motor backward off
}


void turnLeft() {
  digitalWrite(IN1, LOW);   // Stop left motor
  digitalWrite(IN2, LOW);   // Stop left motor backward
  digitalWrite(IN3, HIGH);  // Right motor forward
  digitalWrite(IN4, LOW);   // Right motor backward off
}

// Turn the car right (corrected logic)
void turnRight() {
  digitalWrite(IN1, HIGH);  // Left motor forward
  digitalWrite(IN2, LOW);   // Left motor backward off
  digitalWrite(IN3, LOW);   // Stop right motor
  digitalWrite(IN4, LOW);   // Stop right motor backward
}

// Stop the car
void stopCar() {
  digitalWrite(IN1, LOW);   // Stop left motor forward
  digitalWrite(IN2, LOW);   // Stop left motor backward
  digitalWrite(IN3, LOW);   // Stop right motor forward
  digitalWrite(IN4, LOW);   // Stop right motor backward
}

}
