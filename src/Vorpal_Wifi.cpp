// Wifi for Vorpal
#include "Vorpal_Wifi.h"


AsyncUDP udp;

const char *ssid = "WifiSSID";
const char *password = "WifiPassword";

#ifndef LEDPin
#define LEDPin 2 // if not defined, define internal LED pin as 2 (onboard LED)
#endif

#ifndef BaudRate
#define BaudRate 38400
#endif

HardwareSerial SerialRelay(2); // from hardwareserial.cpp corresponds to pins RX=16 and TX=17

void setupWifi(){
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (udp.listen(1234)) {
    Serial.print("UDP over WiFi Listening on IP: ");
    Serial.println(WiFi.localIP());

    udp.onPacket([](AsyncUDPPacket packet) {

     /* Serial.print("Received Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      */

      String receivedData = String((char*)packet.data());
      SerialRelay.begin(BaudRate);
      SerialRelay.print(receivedData);
      SerialRelay.println();

      /*
      if (receivedData == "LED_OFF") {
        Serial.println("Turning LED off");
        digitalWrite(LEDPin, LOW);
          udp.broadcast("Turning LED off");
      } else if (receivedData == "LED_ON") {
        Serial.println("Turning LED on");
        digitalWrite(LEDPin, HIGH);
          udp.broadcast("Turning LED on");
      }*/

      // packet.printf("Got %u bytes of data", packet.length());
    });
	  }
}


  
