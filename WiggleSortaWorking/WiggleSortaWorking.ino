class Strand {
    unsigned long onTime;
    int magStateA, magStateB, pushPin, pullPin;
    unsigned long previousMillis;
    boolean pull, push, play;
  public:
    Strand(int a, int b) {
      pushPin = a;
      pullPin = b;
      pinMode(pushPin, OUTPUT);
      pinMode(pullPin, OUTPUT);
      magStateA = LOW;
      magStateB = LOW;
      previousMillis = 0;
      pull = true;
      push = false;
      play = true;
    }

    void setInterval(int val) {
      onTime = val;
    }

    void Wiggle() {
      unsigned long currentMillis = millis();
      if (play) {
        if (currentMillis - previousMillis >= onTime) {
          pull = !pull;
          push = !push;
          if (pull) {
            magStateB = HIGH;
          }
          if (!pull) {
            magStateB = LOW;
          }
          if (push) {
            magStateA = HIGH;
          }
          if (!push) {
            magStateA = LOW;
          }
          digitalWrite(pushPin, magStateA);
          digitalWrite(pullPin, magStateB);
          previousMillis = currentMillis;
        }
      }
    }
    void pause () {
      play = false;
    }
    void restart () {
      play = true;
    }
};

Strand strand[9] = { Strand(2, 3), Strand(4, 5), Strand(6, 7),
                     Strand(8, 9), Strand(10, 11), Strand(12, 13),
                     Strand(14, 15), Strand(16, 17), Strand(18, 19)
                   };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 9; i++) {
    Serial.println(i);
    strand[i].setInterval(150);
    strand[i].Wiggle();
  }
}
 int counter=0;
void loop() { 
  moveTogether();
  counter++;
  if (counter >20000){
    for(int i=0; i<9; i++){
      int x = 100*getRandom();
      strand[i].setInterval(x);
    }
    counter =0;
  }
}

int getRandom(){
  return random(0, 9);
}

void moveTogether() {
  int nTimes = getRandom();
  int count = 0;
  while (nTimes > count) {
    for (int i = 0; i < 9; i++) {
      strand[i].Wiggle();
      count++;
    }
  }

}

void ripple() {
  int nTimes = getRandom();
  unsigned long  currentMillis = millis();
  unsigned long previousMillis = 0;
  unsigned long pauseTime = 650;
  int count = 0;
  for (int j = 0; j < 9; j++) {
    strand[j].pause();
  }
  while (nTimes > count) {
    for (int i = 0; i < 9; i++) {
      strand[i].setInterval(300);
      strand[i].restart();
      if (currentMillis - previousMillis >= pauseTime) {
        strand[i].pause();
      }
    }
    count++;
  }
  randomWiggles();
}

void randomWiggles() {
  int nTimes = getRandom();
  int count = 0;
  int pace;
  while (nTimes > count) {
    for (int i = 0; i < 9; i++) {
      randomSeed(A4);
      switch (random(0, 10)) {
        case 0:
          pace = 100;
          break;
        case 1:
          pace = 150;
          break;
        case 2:
          pace = 200;
          break;
        case 3:
          pace = 300;
          break;
        case 4:
          pace = 350;
          break;
        case 5:
          pace = 400;
          break;
        case 6:
          pace = 450;
          break;
        case 7:
          pace = 500;
          break;
        case 8:
          pace = 550;
          break;
        case 9:
          pace = 600;
          break;
        default:
          pace = 300;
          break;
      }
      strand[i].setInterval(pace);
    }
    count++;
  }
}
