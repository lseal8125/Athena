// IF THIS DOES NOT WORK LOOK AT THE CUSTOM THING WITH KEYBOARD!!!!!
//#include "MyKeyboard/src/MyKeyboard.h"
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"
#include "USBHID.h"
#include <ArduinoBLE.h>

const char* serviceUuid = "19B10000-E8F2-537E-4F6C-D104768A1214";
const char* charUuid    = "19B10001-E8F2-537E-4F6C-D104768A1214";

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

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  Serial.println("Central ready. Scanning for Peripheral...");
  BLE.scanForUuid(serviceUuid);
}
void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.println("'");

    BLE.stopScan();

    monitorPeripheral(peripheral);

    Serial.println("Peripheral disconnected. Resuming scan...");
    BLE.scanForUuid(serviceUuid);
  }
}
void monitorPeripheral(BLEDevice peripheral) {
  if (!peripheral.connect()) {
    Serial.println("Failed to connect!");
    return;
  }

  if (!peripheral.discoverAttributes()) {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  BLECharacteristic dataChar = peripheral.characteristic(charUuid);

  if (!dataChar) {
    Serial.println("Characteristic not found!");
    peripheral.disconnect();
    return;
  }

  // Subscribe to receive automatic updates whenever the Peripheral writes a new value
  if (dataChar.canSubscribe()) {
    dataChar.subscribe();
  }

  while (peripheral.connected()) {
    if (dataChar.valueUpdated()) {
      int receivedValue = 0;
      dataChar.readValue(receivedValue);

      Serial.print("Received value: ");
      Serial.println(receivedValue);
    }
  }
}

void Keypressed(){
  for (int row : ROWS){
    digitalWrite(row, LOW);
    delayMicroseconds(5);

    for (int col : COLUMNS){
      if (digitalRead(col) == LOW){
        Serial.println(String("Column:") + col + " Row:" + row);
      }
    }

    digitalWrite(row, HIGH);
  }
}
/*
  calculates key code though col and row then sends the code to USB HID
*/
void SendKeyCode(int col, int row) {
  
//  uint8_t keycode = keymap[String("col" + col)][String("row" + row)];
  //PUT IN A MODIFIER SPOT HERE THIS IS CTRL ALT SHIFT AND I THINK GUI IS CMD/SUPER
  if (col == 6 && row == 12) {
    // HID_REPORT report = BuildKeyReport();
    // Keyboard.send(&report);

    // delay(10);
    // // Release keys
    // Keyboard.send(&report);

    // Serial.println("should be shift+aing rn...");

    // Serial.println("new test");
    // delay(10);
    // uint8_t buf[8] = {0}; 
    // buf[0] = 0x02;
    // buf[2] = 0x04;
    // Serial.write(buf, 8); // Send 8-byte report
    // Serial.println("did it work?");
    // delay(10);

    // uint8_t buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // buf[0] = 0x02; // Left Shift Modifier
    // buf[2] = 0x04; // HID code for 'A'
    
    // Serial.write(buf, 8); 
    // delay(10); 

    // // 2. Release All Keys (The "All Up" Report)
    // buf[0] = 0;
    // buf[2] = 0;
    // Serial.write(buf, 8); 
    
    // Serial.println("Sent Shift+A and released.");

    /*HID_REPORT report;
    report.length = 8;

    memset(report.data, 0, 8);

    report.data[0] = 0x02; // Left Shift modifier
    report.data[2] = 0x04;

    for (int i = 0; i < 8; i++) report.data[i] = 0;
    // Send the "Pressed" state
    HID.send(&report);
    delay(10);

    
    
    memset(report.data, 0, 8);

    // Send the "Released" state (All zeros)
    HID.send(&report);

    Serial.println("HID Report Sent: Shift + A");*/

  }
  
//  if (keycode.isNull()) {
//    Serial.println("no value in keymap");
//  }

  // might need to rework sendReport() more, or find a way to call HID() in this scope. look into that sometime.
  // how do i handle multi-key?

  // Format: key_code(usage_id, modifier)
  // Keyboard.key_code(0x04); 

  return;

}
HID_REPORT BuildKeyReport() {
    HID_REPORT report;

    report.length = 8;              // keyboard reports are 8 bytes
    memset(report.data, 0, 8);

    report.data[0] = 0x02;          // Left Shift modifier
    report.data[2] = 0x04;          // A key

    return report;
}

/*
  I want the writing of keys to make sense and be adaptable. Something like this:
  detect keypress, see (column, row), match to yaml file, use keycode.
  for this reason yaml needs to have column, row stored in it. NOT YAML USING JSON!!!!!
*/
/*
  how loop will look:
  loop(i)(COLUMNS){
    setcol[i].HIGH
    loop(j)(ROWS){
      if ROWS[i].IsHIGH() cwl(Column: i Row: j is pressed)
    }
  }
*/





