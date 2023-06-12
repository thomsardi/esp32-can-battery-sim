#include <Arduino.h>
#include <CAN.h>
#include <DataMap.h>

// CANDataMap canDataMap(0);
CANDataMap canDataMap[16] = {
  CANDataMap(1),
  CANDataMap(2),
  CANDataMap(3),
  CANDataMap(4),
  CANDataMap(5),
  CANDataMap(6),
  CANDataMap(7),
  CANDataMap(8),
  CANDataMap(9),
  CANDataMap(10),
  CANDataMap(11),
  CANDataMap(12),
  CANDataMap(13),
  CANDataMap(14),
  CANDataMap(15),
  CANDataMap(16),
};
int batId = 0;
int dataId = 0;
int packVoltage = 4500;
int packCurrent = 0;
int packSoc = 0;
bool isDecrease = false;
CANDataMap *dataP = canDataMap;
uint8_t (*p)[8] = canDataMap[0].data;

// uint8_t data[11][8] = {
//   {0x56, 0x61, 0x00, 0x50, 0x02, 0x64, 0x01, 0x64},
//   {0x31, 0x31, 0x49, 0x49, 0x49, 0x4b, 0x47, 0x45},
//   {0x15, 0x56, 0x15, 0x56, 0x15, 0x56, 0x15, 0x56},
//   {0x17, 0x56, 0x16, 0x56, 0x15, 0x56, 0x16, 0x56},
//   {0x17, 0x56, 0x17, 0x56, 0x16, 0x56, 0x16, 0x56},
//   {0x17, 0x56, 0x17, 0x56, 0x64, 0x64, 0x64, 0x5e},
//   {0x15, 0x56, 0x17, 0x56, 0x49, 0x4b, 0x42, 0xfc},
//   {0x64, 0x63, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64},
//   {0x27, 0x5a, 0x64, 0x64, 0xe1, 0x6f, 0x61, 0x64},
//   {0x0e, 0x57, 0x64, 0x64, 0xf4, 0x59, 0x64, 0x64},
//   {0x52, 0x64, 0x59, 0x5f, 0x5a, 0x29, 0x64, 0x00}
// };

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  // CAN.setPins(5,4);
  delay(100);
  if (!CAN.begin(250E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  // p = canDataMap[0].data;
  delay(100);
}

void loop() {
  // int packetSize = CAN.parsePacket();

  // if (packetSize) {
  //   // received a packet
  //   Serial.print("Received ");

  //   if (CAN.packetExtended()) {
  //     Serial.print("extended ");
  //   }

  //   if (CAN.packetRtr()) {
  //     // Remote transmission request, packet contains no data
  //     Serial.print("RTR ");
  //   }

  //   Serial.print("packet with id 0x");
  //   Serial.print(CAN.packetId(), HEX);

  //   if (CAN.packetRtr()) {
  //     Serial.print(" and requested length ");
  //     Serial.println(CAN.packetDlc());
  //   } else {
  //     Serial.print(" and length ");
  //     Serial.println(packetSize);

  //     // only print packet data for non-RTR packets
  //     while (CAN.available()) {
  //       // Serial.print((char)CAN.read());
  //       Serial.print(CAN.read());
  //     }
  //     Serial.println();
  //   }

  //   Serial.println();
  // }
  
  if (dataId > 10)
  {
    dataId = 0;
  }
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  // Serial.print("Sending packet ... ");

  // CAN.beginPacket(0x12);
  // CAN.write('h');
  // CAN.write('e');
  // CAN.write('l');
  // CAN.write('l');
  // CAN.write('o');
  // CAN.endPacket();

  // Serial.println("done");

  // delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  // Serial.print("Sending extended packet ... ");
  
  // Serial.print("Frame Id : ");
  // Serial.println(dataP->frameId[0], HEX);
  for (size_t i = 0; i < 16; i++) // iterate over frame id, has 16 device
  {
    CANDataMap *dataMapPointer = dataP + i;
    dataMapPointer->updatePackVoltage(5000);
    dataMapPointer->updatePackCurrent(513);
    dataMapPointer->updatePackSoc(257);
    if(dataId == 0)
    {
      // dataMapPointer->updatePackVoltage(packVoltage);
      // dataMapPointer->updatePackCurrent(packCurrent);
      // dataMapPointer->updatePackSoc(packSoc);
    }
    p = dataMapPointer->data;
    // for (size_t j = 0; j < 11; j++) // iterate over each pack of data frame (1 data frame = 8 bytes )
    // {
    //   Serial.print("frame Id : ");
    //   Serial.println(String(dataMapPointer->frameId[j], HEX));
    //   CAN.beginExtendedPacket(dataMapPointer->frameId[j]);
    //   Serial.print("Data : ");
    //   for (size_t k = 0; k < 8; k++) // iterate over data frame, 1 data frame = 8 bytes
    //   {
    //     Serial.print((uint8_t)canDataMap[i].data[j][k], HEX);
    //     Serial.print(" ");
    //   }
    //   Serial.println();
    //   CAN.write(*(p+i), 8);
    //   CAN.endPacket();
    //   delay(20);
    // }    
    Serial.print("frame Id : ");
    Serial.println(String(dataMapPointer->frameId[dataId], HEX));
    CAN.beginExtendedPacket(dataMapPointer->frameId[dataId]);
    Serial.print("Data : ");
    for (size_t j = 0; j < 8; j++)
    {
      Serial.print((uint8_t)canDataMap[i].data[dataId][j], HEX);
      Serial.print(" ");
    }
    Serial.println();
    CAN.write(*(p+dataId), 8);
    CAN.endPacket();
    delay(20);
  }
  
  // Serial.println("done");
  if(dataId == 0)
  {
    if(!isDecrease)
    {
      packVoltage += 50;
      packCurrent += 10;
      packSoc += 5;
      if(packVoltage >= 5000)
      {
        packVoltage = 5000;
        packCurrent = 100;
        packSoc = 50;
        isDecrease = true;
      }
    }
    else
    {
      packVoltage -= 50;
      packCurrent -= 10;
      packSoc -= 5;
      if(packVoltage <= 4500)
      {
        packVoltage = 4500;
        packCurrent = 0;
        packSoc = 0;
        isDecrease = false;
      }
    }
    // delay(5000);
  }
  dataId++;
  // Serial.println("Pack Voltage : " + String(packVoltage));
  // delay(1000);
}