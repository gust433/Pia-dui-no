
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define DO T4
#define RE T6
#define MI T8
#define FA T3
#define SOL T10
#define LA T12
#define SI T1
#define ccharp T5
#define dcharp T7
#define fcharp T9
#define gcharp T11
#define acharp T13

#define THRESHOLD_LOW 80
#define THRESHOLD_HIGH 190

#define TOPIC_NOTE TOPIC_PREFIX "/note"


bool isTouched1 = false;
bool isTouched2 = false;
bool isTouched3 = false;
bool isTouched4 = false;
bool isTouched5 = false;
bool isTouched6 = false;
bool isTouched7 = false;
bool isTouched8 = false;
bool isTouched9 = false;
bool isTouched10 = false;
bool isTouched11 = false;
bool isTouched12 = false;




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
  mqtt.subscribe(TOPIC_NOTE);
}


void mqtt_callback(char* topic, byte* payload, unsigned int length) {
}

void setup() {
  Serial.begin(115200);
  connect_wifi();
  connect_mqtt();
}


unsigned long previousMillis = 0;
const long interval = 100;  // Send a message every 0.1 second

void loop() {
  unsigned long currentMillis = millis();

  // If the interval has passed, perform an action (e.g., send a message)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //read value
    int touchValue1 = touchRead(DO) / 1000;
    int touchValue2 = touchRead(RE) / 1000;
    int touchValue3 = touchRead(MI) / 1000;
    int touchValue4 = touchRead(FA) / 1000;
    int touchValue5 = touchRead(SOL) / 1000;
    int touchValue6 = touchRead(LA) / 1000;
    int touchValue7 = touchRead(SI) / 1000;
    int touchValue8 = touchRead(ccharp) / 1000;
    int touchValue9 = touchRead(dcharp) / 1000;
    int touchValue10 = touchRead(fcharp) / 1000;
    int touchValue11 = touchRead(gcharp) / 1000;
    int touchValue12 = touchRead(acharp) / 1000;

    Serial.println(touchValue10);
    //DO note
    if ((touchValue1 > THRESHOLD_LOW) && (!isTouched1)) {
      Serial.println("NoteDO");
      isTouched1 = true;
      String payload = "C";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue1 < THRESHOLD_LOW)) {
      isTouched1 = false;
    }
    //RE note
    //Serial.println(touchValue2);
    if ((touchValue2 > THRESHOLD_LOW) && (!isTouched2)) {
      Serial.println("NoteRE");
      isTouched2 = true;
      String payload = "D";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue2 < THRESHOLD_LOW)) {
      isTouched2 = false;
    }

    //MI note GOOD
    if ((touchValue3 > THRESHOLD_LOW) && (!isTouched3)) {
      Serial.println("NoteMI");
      isTouched3 = true;
      String payload = "E";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue3 < THRESHOLD_LOW)) {
      isTouched3 = false;
    }

    // FA note Amos
    if ((touchValue4 > THRESHOLD_LOW) && (!isTouched4)) {
      Serial.println("NoteFA");
      isTouched4 = true;
      String payload = "F";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue4 < THRESHOLD_LOW)) {
      isTouched4 = false;
    }

    //SOL note BAD
    //Serial.println(touchValue5);
    if ((touchValue5 > THRESHOLD_LOW) && (!isTouched5)) {
      Serial.println("NoteSOL");
      isTouched5 = true;
      String payload = "G";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue5 < THRESHOLD_LOW)) {
      isTouched5 = false;
    }

    //LA note
    //Serial.println(touchValue6);
    if ((touchValue6 > THRESHOLD_LOW) && (!isTouched6)) {
      Serial.println("NoteLA");
      isTouched6 = true;
      String payload = "A";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue6 < THRESHOLD_LOW)) {
      isTouched6 = false;
    }

    //SI note
    //Serial.println(touchValue7);
    if ((touchValue7 > THRESHOLD_LOW) && (!isTouched7)) {
      Serial.println("NoteSI");
      isTouched7 = true;
      String payload = "B";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue7 < THRESHOLD_LOW)) {
      isTouched7 = false;
    }
    //Serial.println(touchValue8);
    //C# note
    if ((touchValue8 > THRESHOLD_LOW) && (!isTouched8)) {
      Serial.println("c#");
      isTouched8 = true;
      String payload = "C#";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue8 < THRESHOLD_LOW)) {
      isTouched8 = false;
    }
    //Serial.println(touchValue9);
    //D# note
    if ((touchValue9 > THRESHOLD_LOW) && (!isTouched9)) {
      Serial.println("d#");
      isTouched9 = true;
      String payload = "D#";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue9 < THRESHOLD_LOW)) {
      isTouched9 = false;
    }
    //Serial.println(touchValue10);
    //F# note
    if ((touchValue10 > THRESHOLD_LOW) && (!isTouched10)) {
      Serial.println("f#");
      isTouched10 = true;
      String payload = "F#";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue10 < THRESHOLD_LOW)) {
      isTouched10 = false;
    }
    //Serial.println(touchValue11);
    //G# note
    if ((touchValue11 > THRESHOLD_LOW) && (!isTouched11)) {
      Serial.println("g#");
      isTouched11 = true;
      String payload = "G#";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue11 < THRESHOLD_LOW)) {
      isTouched11 = false;
    }
    //Serial.println(touchValue12);
    //A# note
    if ((touchValue12 > THRESHOLD_LOW) && (!isTouched12)) {
      Serial.println("a#");
      isTouched12 = true;
      String payload = "A#";
      mqtt.publish(TOPIC_NOTE, payload.c_str());

    } else if ((touchValue12 < THRESHOLD_LOW)) {
      isTouched12 = false;
    }
  }
  mqtt.loop();
  
}
