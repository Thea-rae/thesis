#include <Servo.h>
class Servi {
    Servo servo;              // the servo
    public: int pos;              // current servo position
    int increment =1;        // increment to move for each interval
    int updateInterval;      // interval between updates
    int posMax;
    unsigned long lastUpdate; // last update of position

  public:
    Servi(int interval, int ma) {
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
int SPEED = 1;
Servi servi0(10,180);
Servi servi1(20, 180);
Servi servi3(10, 180);
Servi servi2(20, 180);

void setup() {
  Serial.begin(9600);
  servi0.Attach(2);//needs to be a PWM pin
  servi1.Attach(3);
  servi2.Attach(4);
  servi3.Attach(5);
}

void loop() {
  servi0.Update();
  servi1.Update();
  servi2.Update();
  servi3.Update();
}

