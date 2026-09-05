#if __has_include(<Servo.h>)
  #include <Servo.h>
#else
  #include <Arduino.h>

  class Servo {
  public:
    void attach(int) {}
    void write(int) {}
    int read() { return 90; }
    bool attached() { return true; }
    void detach() {}
  };
#endif

// --- Pin Definitions ---
const int SERVO_PIN = 3;
const int TRIG_PIN  = 12;
const int ECHO_PIN  = 11;

// Motor Control Pins (L298N)
const int IN1 = 5;  // Left Motor
const int IN2 = 6;  // Left Motor
const int IN3 = 9;  // Right Motor
const int IN4 = 10; // Right Motor

// --- SPEED CALIBRATION ---
// Left is set to 200, Right is 255 to overcome internal friction.
// Adjust these if the car drifts to one side.
int leftSpeed = 200;  
int rightSpeed = 255; 

Servo scanServo;

void setup() {
  // Start the Serial Monitor to see sensor readings (Baud rate: 9600)
  Serial.begin(9600); 

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90); // Set servo to center position
  delay(500);
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // 30ms timeout to prevent code freezing if an echo is missed
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  if (duration == 0) return 400; // Assume path is clear if no echo
  
  return duration * 0.0343 / 2; 
}

// --- MOVEMENT LOGIC (Adjusted for corrected wiring orientation) ---

void moveForward() {
  // Left Motor Forward
  digitalWrite(IN1, LOW); 
  analogWrite(IN2, leftSpeed);
  
  // Right Motor Forward 
  analogWrite(IN3, rightSpeed); 
  digitalWrite(IN4, LOW); 
}

void moveBackward() {
  // Left Motor Reverse
  analogWrite(IN1, leftSpeed); 
  digitalWrite(IN2, LOW);
  
  // Right Motor Reverse
  digitalWrite(IN3, LOW); 
  analogWrite(IN4, rightSpeed); 
}

void stopMotors() {
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // Left goes forward, Right goes backward
  digitalWrite(IN1, LOW); 
  analogWrite(IN2, leftSpeed);
  
  digitalWrite(IN3, LOW); 
  analogWrite(IN4, rightSpeed);  
}

void turnLeft() {
  // Left goes backward, Right goes forward
  analogWrite(IN1, leftSpeed); 
  digitalWrite(IN2, LOW);
  
  analogWrite(IN3, rightSpeed); 
  digitalWrite(IN4, LOW);
}

// --- MAIN LOOP ---

void loop() {
  long distance = getDistance();
  
  // Print the distance to the screen for debugging
  Serial.print("Distance Ahead: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Navigation Logic
  if (distance > 25) { 
    // Clear path ahead
    moveForward();
  } else {             
    // Obstacle detected (less than 25cm)
    stopMotors();
    delay(200);

    // Look Right
    scanServo.write(30);
    delay(400);
    long rightDist = getDistance();

    // Look Left
    scanServo.write(150);
    delay(400);
    long leftDist = getDistance();

    // Return to Center
    scanServo.write(90);
    delay(200);

    // Decide direction based on which side has more space
    if (rightDist > 15 || leftDist > 15) {
      if (rightDist > leftDist) {
        turnRight();
        delay(400); // Tweak this delay to make the turn sharper or wider
      } else {
        turnLeft();
        delay(400);
      }
    } else {
      // Trapped in a tight corner, back up then turn
      moveBackward();
      delay(500);
      turnRight();
      delay(400);
    }
  }
}