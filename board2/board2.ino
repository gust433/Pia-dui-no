
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define RED_GPIO 42
#define GREEN_GPIO 40
#define LDR_GPIO 4
#define SW_PIN 2
#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 1
#define LED5 38
#define LED6 7
#define LED7 39
#define LED8 15
#define LED9 16
#define LED10 17
#define LED11 8
#define LED12 20
#define TOPIC_LED TOPIC_PREFIX "/n"
#define TOPIC_CHORD TOPIC_PREFIX "/chord"
#define TOPIC_LED_RED TOPIC_PREFIX "/led/red"
#define TOPIC_LED_GREEN TOPIC_PREFIX "/led/green"
#define TOPIC_DISPLAY_TEXT TOPIC_PREFIX "/display/text"
#define TOPIC_SWITCH TOPIC_PREFIX "/switch"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WiFiClient wifiClient;
PubSubClient mqtt(MQTT_BROKER, 1883, wifiClient);
uint32_t last_publish;


void connect_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  printf("WiFi MAC address is %s\n", WiFi.macAddress().c_str());
  printf("Connecting to WiFi %s.\n", WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    printf(".");
    fflush(stdout);
    delay(500);
  }
  printf("\nWiFi connected.\n");
}


void connect_mqtt() {
  printf("Connecting to MQTT broker at %s.\n", MQTT_BROKER);
  if (!mqtt.connect("", MQTT_USER, MQTT_PASS)) {
    printf("Failed to connect to MQTT broker.\n");
    for (;;) {}  // wait here forever
  }
  mqtt.setCallback(mqtt_callback);
  mqtt.subscribe(TOPIC_DISPLAY_TEXT);
  mqtt.subscribe(TOPIC_LED_RED);
  mqtt.subscribe(TOPIC_LED_GREEN);
  mqtt.subscribe(TOPIC_LED);
  mqtt.subscribe(TOPIC_CHORD);
}


void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, TOPIC_CHORD) == 0) {
    
    display.setCursor(32, 30);
    display.clearDisplay();
    payload[length] = 0;
    String text = ((char*)payload);
    display.print(text);
    display.display();
  }
  if (strcmp(topic, TOPIC_DISPLAY_TEXT) == 0) {
    display.setCursor(32, 30);
    display.clearDisplay();
    payload[length] = 0;
    String text = ((char*)payload);
    display.print(text);
    display.display();
    
  }

  if (strcmp(topic, TOPIC_LED_RED) == 0) {
    payload[length] = 0;  // null-terminate the payload to treat it as a string
    String value = ((char*)payload);
    if (value == "Correct") {
      digitalWrite(RED_GPIO, LOW);
    } else if (value == "Wrong") {
      digitalWrite(RED_GPIO, HIGH);
      
    } else {
      printf("Invalid payload received.\n");
    }
  }
  if (strcmp(topic, TOPIC_LED_GREEN) == 0) {
    payload[length] = 0;  // null-terminate the payload to treat it as a string
    String value = ((char*)payload);
    if (value == "Wrong") {
      digitalWrite(GREEN_GPIO, LOW);
    } else if (value == "Correct") {
      digitalWrite(GREEN_GPIO, HIGH);
      delay(1000);
      digitalWrite(GREEN_GPIO, LOW);
    } else {
      printf("Invalid payload received.\n");
    }
  }
  if (strcmp(topic, TOPIC_LED) == 0) {
    payload[length] = 0;  // null-terminate the payload to treat it as a string
    String value = ((char*)payload);
    if (value == "Correct" or value == "RESET") {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      digitalWrite(LED6, LOW);
      digitalWrite(LED7, LOW);
      digitalWrite(LED8, LOW);
      digitalWrite(LED9, LOW);
      digitalWrite(LED10, LOW);
      digitalWrite(LED11, LOW);
      digitalWrite(LED12, LOW);
    } else if (value == "C") {
      digitalWrite(LED1, HIGH);
    } else if (value == "C#") {
      digitalWrite(LED2, HIGH);
    } else if (value == "D") {
      digitalWrite(LED3, HIGH);
    } else if (value == "D#") {
      digitalWrite(LED4, HIGH);
    } else if (value == "E") {
      digitalWrite(LED5, HIGH);
    } else if (value == "F") {
      digitalWrite(LED6, HIGH);
    } else if (value == "F#") {
      digitalWrite(LED7, HIGH);
    } else if (value == "G") {
      digitalWrite(LED8, HIGH);
    } else if (value == "G#") {
      digitalWrite(LED9, HIGH);
    } else if (value == "A") {
      digitalWrite(LED10, HIGH);
    } else if (value == "A#") {
      digitalWrite(LED11, HIGH);
    } else if (value == "B") {
      digitalWrite(LED12, HIGH);
    } else {
      
      printf("Invalid payload received.\n");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(48, 47);
  pinMode(RED_GPIO, OUTPUT);
  digitalWrite(RED_GPIO, 0);
  pinMode(GREEN_GPIO, OUTPUT);
  digitalWrite(GREEN_GPIO, 0);
  pinMode(SW_PIN, INPUT_PULLUP);
  connect_wifi();
  connect_mqtt();
  last_publish = 0;
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  delay(2000);
  display.clearDisplay();
  display.setCursor(25, 32);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LED11, OUTPUT);
  pinMode(LED12, OUTPUT);
}

void loop() {

  mqtt.loop();
  
}
