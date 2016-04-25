#include <Servo.h>
class Wiggler {
    // Class Member Variables
    int solenoidPin;
    long OnTime;
    long OffTime;

    // These maintain the current state
    int solenoidState;
    unsigned long previousMillis;

    // Constructor - creates a wiggler
    // and initializes the member variables and state
  public:
    Wiggler(int pin, long on, long off) {
      solenoidPin = pin;
      pinMode(solenoidPin, OUTPUT);

      OnTime = on;
      OffTime = off;

      solenoidState = LOW;
      previousMillis = 0;
    }

    void Update() {
      // check to see if it's time to change the state of the solenoid
      unsigned long currentMillis = millis();

      if ((solenoidState == HIGH) && (currentMillis - previousMillis >= OnTime))
      {
        solenoidState = LOW;  // Turn it off
        previousMillis = currentMillis;  // Remember the time
        digitalWrite(solenoidPin, solenoidState);  // Update the actual solenoid
      }
      else if ((solenoidState == LOW) && (currentMillis - previousMillis >= OffTime))
      {
        solenoidState = HIGH;  // turn it on
        previousMillis = currentMillis;   // Remember the time
        digitalWrite(solenoidPin, solenoidState);   // Update the actual solenoid
      }
    }

    void ChangeOn(long on) {
      OnTime = on;
    }

    void ChangeOff(long off) {
      OffTime = off;
    }
};

class Sweeper {
    Servo servo;              // the servo
    int pos;              // current servo position
    int increment =1;        // increment to move for each interval
    int updateInterval;      // interval between updates
    int posMax;
    unsigned long lastUpdate; // last update of position

  public:
    Sweeper(int interval, int ma) {
      updateInterval = interval;
      posMax = ma;
    }

    void Attach(int pin) {
      servo.attach(pin);
    }

    void Detach() {
      servo.detach();
    }

    void Update() {
      if ((millis() - lastUpdate) > updateInterval) {
        lastUpdate = millis();
        pos += increment;
        servo.write(pos);
        Serial.println(pos);
        if ((pos >= posMax) || (pos <= 0)) {
          increment = -increment;
        }
      }
    }

    void ChangeMax(int ma) {
      posMax = ma;
    }

    void ChangeSpeed(int pace) {
      updateInterval = pace;
    }

};
int MAX = 180;
int SPEED = 15;
int pull = 100;
int count = 0;
Wiggler wiggler(2,100,100);


void setup() {
  Serial.begin(9600);
}

void loop() {
  wiggler.Update();
  
}

