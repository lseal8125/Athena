#include <ArduinoBLE.h>
      
enum {
  GESTURE_NONE  = -1,
  GESTURE_UP    = 0,
  GESTURE_DOWN  = 1,
  GESTURE_LEFT  = 2,
  GESTURE_RIGHT = 3
};

struct DataPacket {
  int col;
  int row;
};

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

int gesture = -1;

BLEService gestureService(deviceServiceUuid); 
BLECharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite, sizeof(DataPacket));

unsigned long previousMillis = 0;

int ROWS[] = { 12, 11, 10, 9, 8 };
int COLUMNS[] = { 7, 6, 5, 4, 3, 2 };

void setup(){
   for (int i : ROWS){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);

  }
  for (int i : COLUMNS){
    pinMode(i, INPUT_PULLUP);
  }

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  BLE.addService(gestureService);
  DataPacket d{};
  gestureCharacteristic.writeValue(d);
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
}

void loop(){

  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {
      if (millis() - previousMillis >= 20) {
         keyPressed();
       }
    }
    
    Serial.println("* Disconnected to central device!");
  }
}

void keyPressed(){
  for (int row : ROWS){
    digitalWrite(row, LOW);
    delayMicroseconds(5);

    for (int col : COLUMNS){
      if (digitalRead(col) == LOW){
        DataPacket packet = { col, row}
        Serial.println(String("Column:") + col + " Row:" + row);
        gestureCharacteristic.writeValue((uint8_t*)&packet, sizeof(data));
      }
    }

    digitalWrite(row, HIGH);
  }
}






