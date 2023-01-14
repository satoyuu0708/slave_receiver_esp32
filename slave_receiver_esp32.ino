// WireSlave Receiver
// by Gutierrez PS <https://github.com/gutierrezps>
// ESP32 I2C slave library: <https://github.com/gutierrezps/ESP32_I2C_Slave>
// based on the example by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the WireSlave library for ESP32.
// Receives data as an I2C/TWI slave device; data must
// be packed using WirePacker.
// Refer to the "master_writer" example for use with this

#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>
#include <Arduino.h>
#include "recive_event.h"
#include <BLEDevice.h>
#include <BLE2902.h>
#include <BLEUtils.h>
#include <BLEServer.h>



#define SDA_PIN 13
#define SCL_PIN 4
#define I2C_SLAVE_ADDR 0x04

#define BLE_LOCAL_NAME "Smart-Sticker11"
#define BLE_SERVICE_UUID "143fe8d4-5197-4675-9d76-d9bbf2450bb4"
// BLEのCharacteristic UUID。適当なUUID(ランダムで生成したものがよい)を設定して下さい。
#define BLE_CHARACTERISTIC_UUID "0fc20cb8-0518-40dd-b5c3-c4637815de40"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
int delayConnect = 500; //切断後，再度受付状態になるまでの時間．



void receiveEvent(int howMany);

//////////////////////Ble通信するための準備///////////////////////

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    Serial.println("connect1");
    deviceConnected = true;
    Serial.println("connect2");
  };

  void onDisconnect(BLEServer *pServer) {
    Serial.println("disconnect");
    deviceConnected = false;
  };
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic) {
    Serial.println("connect4");
    Serial.println("read");
    std::string value = pCharacteristic->getValue();
    Serial.println("connect5");
    pCharacteristic->setValue("スマートステッカーと接続しました");
    Serial.println("connect6");
  };
};

/////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(500000);
  //Wire.begin(I2C_SLAVE_ADDR);
  //Wire.begin(I2C_SLAVE_ADDR, SDA_PIN, SCL_PIN); 
   bool success = WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);

  delay(100);
  matrix.begin();
  //matrix.clear();
  delay(100);

  //////////////////////////Ble通信の開始//////////////////////////////////

  BLEDevice::init(BLE_LOCAL_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
    BLE_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  ////////////////////////////////////////////////////////////////////////


  if (!success) {
    Serial.println("I2C slave init failed");
    while (1) delay(100);
  }

  WireSlave.onReceive(receiveEvent);
}

void loop() {
  //Serial.println("test4");


  WireSlave.update();
  //matrix.drawRGBBitmap(0, 0, car_sample[0], 32, 21);  //LEDmatrixPanelにカメラ画像を表示
  //matrix.drawPixel(10, 10, 10);
  //Serial.println("test5");

  delay(1);
}
