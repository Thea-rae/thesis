
class Solenoid {
    // Class Member Variables
    int solenoidPin;
    long OnTime;
    long OffTime;

    // These maintain the current state
    int solenoidState;
    unsigned long previousMillis;

    // Constructor - creates a solenoid
    // and initializes the member variables and state
  public:
    Solenoid(int pin, long on, long off) {
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

      if ((solenoidState == HIGH) && (currentMillis - previousMillis >= OnTime)) {
        solenoidState = LOW;  // Turn it off
        previousMillis = currentMillis;  // Remember the time
        digitalWrite(solenoidPin, solenoidState);  // Update the actual solenoid
      } else if ((solenoidState == LOW) && (currentMillis - previousMillis >= OffTime)){
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


Solenoid solenoid(3,100,200);
Solenoid solenoid2(5,300, 400);
Solenoid solenoid3(6, 100, 100);

void setup() {
}

void loop() {
  solenoid.Update();
  solenoid2.Update();
  solenoid3.Update();
}

