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




#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04



void receiveEvent(int howMany);




void setup() {
  Serial.begin(500000);
  Wire.begin(I2C_SLAVE_ADDR);
  delay(10);
  Serial.println("test1");
 




  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);
  if (!success) {
    Serial.println("I2C slave init failed");
    while (1) delay(100);
  }

  WireSlave.onReceive(receiveEvent);
  
  
}

void loop() {
  //Serial.println("test4");

  WireSlave.update();
 //Serial.println("test5");

  delay(1);
}
