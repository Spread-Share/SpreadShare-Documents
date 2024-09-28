// /*******************************************************************
// * Copyright         : 2024  Saydam
// * File Name         : iBeacon.ino
// * Description       : This file uses the Esp32 as an iBeacon to test the application
// *                    
// * Revision History  :
// * Date		Author 			Comments
// * ------------------------------------------------------------------
// * 28/09/2024	Saydam Arda   Created
// *
// /******************************************************************/


#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Generate new UUID
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "b3202a0a-26c3-4bd2-9855-cf231924ec0c"
#define CHARACTERISTIC_UUID "0ad390a5-da26-43fd-b349-3a35687e611b"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("SpreadShare Beacon");  // set the device name
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World!");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void loop() {
  delay(2000);
}