/*
  pins 11-15: rows
  pins 5-10: colums
*/

int ROWS[] = { 12, 11, 10, 9, 8 };
int COLUMNS[] = { 7, 6, 5, 4, 3, 2 };

void setup() {
  for (int i : ROWS){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);

  }
  for (int i : COLUMNS){
    pinMode(i, INPUT_PULLUP);
  }
  Serial.begin(9600);
}
void loop() {

  for (int i : ROWS){
    digitalWrite(i, LOW);
    delayMicroseconds(5);

    for (int j : COLUMNS){
      if (digitalRead(j) == LOW){
        Serial.println(String("Column:") + j + " Row:" + i);
      }
    }

    digitalWrite(i, HIGH);
  }
}

/*
  how loop will look:
  loop(i)(COLUMNS){
    setcol[i].HIGH
    loop(j)(ROWS){
      if ROWS[i].IsHIGH() cwl(Column: i Row: j is pressed)
    }
  }
*/