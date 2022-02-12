#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const int pin34 = 34;
const int pin35 = 35;
int val34 = 0;
int val35 = 0;
int relay_pin = 25;
int led_pin = 26;
char* relay_pin_status = "relay_pin: LOW";

void setup() {
  Serial.begin(115200);
  pinMode (relay_pin, OUTPUT);
  pinMode (relay_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);

  digitalWrite(relay_pin, LOW);
  relay_pin_status = "relay_pin: LOW";

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(1000);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
    
  WiFi.begin(ssid, password);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting WiFi...");
    tries +=1;
    if(tries > 10){
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//CALLBACK
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageIn;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageIn += (char)message[i];
  }
  Serial.println();
  
  if (String(topic) == "esp32/status"){
    Serial.println("status");
    val34 = analogRead(pin34);
    val35 = analogRead(pin35);
    char string34[8];
    sprintf(string34,"%ld", val34);
    client.publish("esp32/in", string34);
    char string35[8];
    sprintf(string35,"%ld", val35);
    client.publish("esp32/in", string35);   
    client.publish("esp32/in", relay_pin_status);
    
  }
  if (String(topic) == "esp32/door/house/open"){
    if(messageIn == "1234"){
      Serial.println("Open Door");
      digitalWrite(relay_pin, HIGH);
      relay_pin_status = "relay_pin: HIGH";
      delay(5000);
      digitalWrite (relay_pin, LOW);
      relay_pin_status = "relay_pin: LOW";
      client.publish("esp32/door/house/status", "Die Haustür wurde geöffnet.");
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/status");
      client.subscribe("esp32/door/house/open");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void send(int val, char* topic){
//  float volt = (float)val/4095*30;
  char voltString[8];
//  dtostrf(volt, 1, 2, voltString);
  sprintf(voltString,"%ld", val);
  client.publish(topic, voltString);

}
void loop() {
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    val34 = analogRead(pin34);
    val35 = analogRead(pin35);

    if (val34 > 10) {
      Serial.println(val34);
      send(val34, "esp32/gong_house");
      lastMsg = now;
    }
    if (val35 > 10) {
      Serial.println(val35);
      send(val35, "esp32/gong_home");
      lastMsg = now;
    }
  }
  delay(100);
}
