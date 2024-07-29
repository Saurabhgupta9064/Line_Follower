// Pin definitions
#define LCS A1
#define CS A2
#define RCS A3
#define LEFT_MOTOR 5
#define LEFT_MOTOR_PSEUDO 6
#define RIGHT_MOTOR 9
#define RIGHT_MOTOR_PSEUDO 10

// Sensor threshold values 
#define THRESH 500

// Motor speed ki value
#define BASE_SPEED 70
#define TURN_SPEED 50

void setup() {
// Set pin modes for sensors and motors
  pinMode(LCS, INPUT);
  pinMode(CS, INPUT);
  pinMode(RCS, INPUT);
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
}

void loop() {

  int left_center = analogRead(LCS);
  int center = analogRead(CS);
  int right_center = analogRead(RCS);
  
  // Check if all sensors are reading black
  if (left_center > THRESH && center > THRESH && right_center > THRESH) {
    // Reached the end of the maze, stop the motors
    digitalWrite(LEFT_MOTOR, LOW);
    digitalWrite(RIGHT_MOTOR, LOW);
    digitalWrite(LEFT_MOTOR_PSEUDO, LOW);
    digitalWrite(RIGHT_MOTOR_PSEUDO, LOW);
  }
  
  // Determine which direction to turn based on the sensor readings
  else if (left_center < THRESH && center > THRESH && right_center < THRESH) {

    // On a straight line, go straight

    analogWrite(LEFT_MOTOR, BASE_SPEED);
    analogWrite(RIGHT_MOTOR, BASE_SPEED);
    digitalWrite(LEFT_MOTOR_PSEUDO, LOW);
    digitalWrite(RIGHT_MOTOR_PSEUDO, LOW);
  }

  else if (left_center > THRESH) {

    // Turn slightly left

    digitalWrite(LEFT_MOTOR, LOW);
    analogWrite(RIGHT_MOTOR, BASE_SPEED);
    digitalWrite(LEFT_MOTOR_PSEUDO, LOW);
    digitalWrite(RIGHT_MOTOR_PSEUDO, LOW);
  }

  else if (right_center > THRESH) {

    // Turn slightly right
    
    analogWrite(LEFT_MOTOR, BASE_SPEED);
    digitalWrite(RIGHT_MOTOR, LOW);
    digitalWrite(LEFT_MOTOR_PSEUDO, LOW);
    digitalWrite(RIGHT_MOTOR_PSEUDO, LOW);
  }
  else if (left_center < THRESH && center < THRESH && right_center < THRESH) {

    // white end of the maze
    while (left_center < THRESH && center > THRESH && right_center < THRESH) {
      analogWrite(LEFT_MOTOR, TURN_SPEED);
      analogWrite(RIGHT_MOTOR, 0); 
      analogWrite(RIGHT_MOTOR_PSEUDO, TURN_SPEED);
      analogWrite(LEFT_MOTOR_PSEUDO, 0);
    }
  }
}