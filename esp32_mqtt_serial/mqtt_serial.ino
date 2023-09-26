/*
  Print Mqtt messages to serial
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

// WIFI code
const char* ssid = "cchs";
const char* password = "";
const char* mqtt_topic = "esp32/output";

const char* mqtt_server = "192.168.0.220";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  //We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  if (String(topic) == mqtt_topic) {
    for (int i = 0; i < length; i++) {
      Serial.print((char)message[i]);
    }
    Serial.println();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.print("connected to topic: ");
      Serial.println(mqtt_topic);
      // Subscribe
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(9600);

  setup_wifi();
  Serial.println("Setting Up Wifi");

  client.setServer(mqtt_server, 1883);
  Serial.println("Setting Up Mqtt Server");

  client.setCallback(callback);
}

// the loop routine runs over and over again forever:
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();


}