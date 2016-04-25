


MCP wiggleChip(0, 10);
const int strand[17] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 5, 6};

void setup() {
  Serial.begin(9600);
  Serial.println("hi");
  wiggleChip.begin();
  for (int i = 1; i < 16; i++) {
    Serial.println(i);
    wiggleChip.pinMode(i, LOW);
  }
  pinMode(strand[16], OUTPUT);
  Serial.println(16);
  pinMode(strand[17], OUTPUT);
  Serial.println(17);
}

void loop() {
  writeLow();
  cycleOnOff();
}

void writeLow() {
  for (int i = 0; i < 18; i++) {
    if (i < 16) {
      wiggleChip.digitalWrite(i, LOW);
    } else {
      digitalWrite(strand[i], LOW);
    }
  }
}
void cycleOnOff() {
  for (int i = 1; i < 18;  i++) {
    Serial.println(i);
    if (i < 16) {
      wiggleChip.digitalWrite(i, HIGH);
      delay(300);
      wiggleChip.digitalWrite(i, LOW);
    } else {
//      digitalWrite(strand[i], HIGH);
//      delay(300);
//      digitalWrite(strand[i], LOW);
    }
  }
}


void cycleOff() {
  for (int i = 0; i < 9;  i++) {

  }
}
