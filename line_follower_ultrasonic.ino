#include <NewPing.h> // Include the NewPing library

// Motor control pins
#define in1 27 // Motor 1 L298 Pin in1
#define in2 14 // Motor 1 L298 Pin in2
#define in3 25 // Motor 2 L298 Pin in3
#define in4 26 // Motor 2 L298 Pin in4

// IR sensor pins
#define L_S 13 // IR sensor Left
#define R_S 12 // IR sensor Right

// Ultrasonic sensor pins
#define echo 32    // Echo pin
#define trigger 33 // Trigger pin
#define MAX_DISTANCE 200 // Maximum distance in cm

NewPing sonar(trigger, echo, MAX_DISTANCE); // Create NewPing object

void setup() {
    Serial.begin(115200);

    // Set motor control pins as OUTPUT
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    
    // Set IR sensor pins as INPUT
    pinMode(L_S, INPUT);
    pinMode(R_S, INPUT);
}

void loop() {
    // Measure distance using ultrasonic sensor
    float distance = sonar.ping_cm();
    
    // Print the distance to Serial
    Serial.print("Distance: ");
    Serial.println(distance);
    
    // Check if distance is less than 15 cm
    if (distance < 15) {
        stopMotors();
        delay(2000);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        Serial.println("TURN AROUND");
        delay(1500);

    } else {
        followLine();
    }

    delay(100); // Delay for stability
}

// Function to stop all motors
void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

// Function to follow line based on IR sensor input
void followLine() {
    int leftSensorValue = digitalRead(L_S);
    int rightSensorValue = digitalRead(R_S);

    if (leftSensorValue == HIGH && rightSensorValue == LOW) {
        // Move right
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        Serial.println("RIGHT");
    } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
        // Move left
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        Serial.println("LEFT");
        
    } 
    else if (leftSensorValue == LOW && rightSensorValue == LOW) {
        // Move left
        stopMotors();
        delay(2000);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        Serial.println("TURN AROUND");
        delay(500);
        
    } 
    
    
    else {
        // Move forward
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        Serial.println("FORWARD");
    }
}
