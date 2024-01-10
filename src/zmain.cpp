// Alpaca Ascom control of flat-panel running on FastLED compatible LED strips. 

#include <Arduino.h>

#include "WiFi.h"
#include "WebServer.h"
#include "AsyncUDP.h"
#include "config.h"
#include "ArduinoJson.h"

// enable debugging values
const bool DEBUG = true;

const char *ssid = _SSID;           // your network SSID (name)
const char *password = _PASSWORD;   // your network password (use for WPA, or use as key for WEP)

unsigned const int discoveryPort = 32227;  //The Alpaca Discovery port
unsigned const int alpacaPort = 4567;  //The (fake) port that the Alpaca API would be available on
const char *uuid = "8de70ae6-ce7b-4741-ae69-1294a316e906";

AsyncUDP udp_discovery;
WebServer server(alpacaPort);

// LED DEBUGGING
#define BLINK_INTERVAL 1000 //every 1000 ms
unsigned long last_blink;
int led_state;

// LED CONTROL - FASTLED
// hardcode colour to neutral white

// default is that the LEDs are off, waiting for commands to turn on

/*
******* REMEMBER TO EDIT CONFIG.H FOR YOUR CONFIGURATION *******
*/

void discoveryRequest(AsyncUDPPacket &packet);
void ConfiguredDevicesRequest();
void ApiVersionsRequest();
void DescriptionRequest();
void handleNotFound();

void setup ()
{
  // setup serial
  Serial.begin(115200);

  // setup LED Pin
  pinMode(LED_BUILTIN, OUTPUT);
  last_blink = millis();
  led_state = HIGH;
  digitalWrite(LED_BUILTIN, led_state);

  // setup WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
      Serial.println("WiFi Failed");
      while (1)
      {
          delay(1000);
      }
  }
  Serial.print("Connect with IP Address: ");
  Serial.println(WiFi.localIP());

  // SETUP UDP REQUESTS - Discovery
  if (udp_discovery.listen(discoveryPort))
  {
      Serial.println("Listening for discovery requests...");
      udp_discovery.onPacket(discoveryRequest);
      
  } else 
      Serial.println("failed to add listener for alpaca discovery request");

  // HTTP Server for the command and management api
  server.on("/management/v1/configureddevices", HTTP_GET, ConfiguredDevicesRequest);
  server.on("/management/apiversions", HTTP_GET, ApiVersionsRequest);
  server.on("/management/v1/description", HTTP_GET, DescriptionRequest);

  // Command API For CoverCalibrator
  // We can hardcode the device-number, as we only support 1 device for now. 
  // Only implementing the brightness, states, and max brightness api calls. Everything else will go to "nothandled" and return appropiate error of not implemented.
  server.on("/covercalibrator/0/brightness", HTTP_GET, BrightnessRequest);
  server.on("/covercalibrator/0/calibratorstate", HTTP_GET, CalibratorStateRequest);
  server.on("/covercalibrator/0/coverstate", HTTP_GET, CoverStateRequest); // just returns 200 "NotPresent	int: 0	This device does not have a cover that can be closed independently "
  server.on("/covercalibrator/0/maxbrightness", HTTP_GET, MaxBrightnessRequest);
  // put requests aka. Actual control of the calibrator
  server.on("/covercalibrator/0/calibratoroff", HTTP_PUT, CalibratorOffRequest);
  server.on("/covercalibrator/0/calibratoron", HTTP_PUT, CalibratorOnRequest);

  // TODO implement the last API calls, including the LED state specific stuff. Need to have an LED state to return

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}  // end of setup

void loop ()
{
  // get time
  unsigned long curr_millis = millis();

  // blink led to show we are still running
  if ((curr_millis - last_blink) > BLINK_INTERVAL) {
    // flip led state
    led_state = led_state ? LOW : HIGH;
    digitalWrite(LED_BUILTIN, led_state);
    last_blink = curr_millis;
  }  

  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}  // end of loop


void discoveryRequest(AsyncUDPPacket &packet) {
  // TODO remove unnessecary debug prints
  Serial.print("Received UDP Packet of Type: ");
  Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
  Serial.print(", From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(", To: ");
  Serial.print(packet.localIP());
  Serial.print(":");
  Serial.print(packet.localPort());
  Serial.print(", Length: ");
  Serial.print(packet.length());
  Serial.print(", Data: ");
  Serial.write(packet.data(), packet.length());
  Serial.println();

  // No undersized packets allowed
  if (packet.length() < 16)
      return;

  //Compare packet to Alpaca Discovery string
  if (strncmp("alpacadiscovery1", (char *)packet.data(), 16) != 0)
      return;

  // send a reply, to the IP address with port for webserver
  packet.printf("{\"AlpacaPort\": %d}", alpacaPort);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(403, "text/plain", message);

  Serial.println(message); // debug to see what they ask of us that isn't implemented!
}

void ApiVersionsRequest() {
  Serial.println("Received 'ApiVersions' request");
  Serial.flush();

  JsonDocument doc;

  // handle arguments/parameters of: ClientID & ClientTransactionID
  if (server.hasArg("ClientID")) {
    doc["ClientID"] = server.arg("ClientID");
  }  
  if (server.hasArg("ClientTransactionID")) {
    doc["ClientTransactionID"] = server.arg("ClientTransactionID");
  }

  JsonArray value = doc["value"].to<JsonArray>();
  value.add(1);

  String output;
  serializeJson(doc, output);

  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "application/json", output);
}

void DescriptionRequest() {
  Serial.println("Received 'Description' request");
  Serial.flush();

  JsonDocument doc;

  // handle arguments/parameters of: ClientID & ClientTransactionID
  if (server.hasArg("ClientID")) {
    doc["ClientID"] = server.arg("ClientID");
  }  
  if (server.hasArg("ClientTransactionID")) {
    doc["ClientTransactionID"] = server.arg("ClientTransactionID");
  }

  JsonObject root = doc.to<JsonObject>();
  JsonObject value = doc["Value"].to<JsonObject>();
  value["ServerName"] = "EspFlatPanel";
  value["Manufacturer"] = "Crowdedlight";
  value["ManufacturerVersion"] = "v1.0.0";
  value["Location"] = "The Milky Way";

  String output;
  serializeJson(doc, output);

  if (DEBUG) {
    serializeJson(doc, Serial);
  }

  server.send(200, "application/json", output);
}

void ConfiguredDevicesRequest() {
  Serial.println("Received 'ConfiguredDevices' request");
  Serial.flush();

  JsonDocument doc;

  // handle arguments/parameters of: ClientID & ClientTransactionID
  if (server.hasArg("ClientID")) {
    doc["ClientID"] = server.arg("ClientID");
  }  
  if (server.hasArg("ClientTransactionID")) {
    doc["ClientTransactionID"] = server.arg("ClientTransactionID");
  }

  JsonObject root = doc.to<JsonObject>();
  JsonArray value = doc["Value"].to<JsonArray>();
  JsonObject object = value.add<JsonObject>();
  object["DeviceName"] = "Esp Flat Panel";
  object["DeviceType"] = "CoverCalibrator";
  object["DeviceNumber"] = 0;
  object["UniqueID"] = uuid;

  String output;
  serializeJson(doc, output);

  if (DEBUG) {
    serializeJson(doc, Serial);
  }

  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "application/json", output);
}