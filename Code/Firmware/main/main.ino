/*
  pins 11-15: rows
  pins 5-10: colums
*/

int ROWS[] = { 12, 11, 10, 9, 8 };
int COLUMNS[] = { 7, 6, 5, 4, 3, 2 };

void setup() {
  for (int i : ROWS){
    pinMode(i, INPUT_PULLUP);
  }
  for (int i : COLUMNS){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);

  }
  Serial.begin(9600);
}
void loop() {

  for (int i : COLUMNS){
    digitalWrite(i, LOW);
    delayMicroseconds(5);

    for (int j : ROWS){
      if (digitalRead(j) == LOW){
        Serial.println(String("Column:") + i + " Row:" + j);
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