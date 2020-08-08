#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <fauxmoESP.h>

#define LED_PIN    15
#define LED_PIN_STRIP    16

#define WIFI_SSID "*****" //TODO: Set your ssid
#define WIFI_PASS "*****" //TODO: Set your password

Adafruit_NeoPixel strip(60, LED_PIN_STRIP, NEO_GRB + NEO_KHZ800);
fauxmoESP fauxmo;

void setup()
{
  Serial.begin(115200);
  strip.clear();
  
  if (wifiSetup()) {
    // Setup fauxmo
    fauxmo.setPort(80);
    fauxmo.enable(true);
    fauxmo.addDevice("Led");

    fauxmo.onSetState([](unsigned char device_id, const char * device_name,
    bool state, unsigned char value) {
      Serial.print("Device name:");
      Serial.println(device_name);

      if (strcmp(device_name, "Led") == 0) {
        Serial.print("Strip status:");
        Serial.print(state);
        Serial.println("");
        // Set RGB Color
        if (state)
        {
          Serial.println("turn on");
          strip.fill(strip.Color(200, 100, 200), 0, 60);
          strip.show();
        }
        else
        {
          Serial.println("turn off");
          turnOffStrip();
        }
      }
    });
  }

  strip.begin(); // This initializes the NeoPixel library.
  strip.show(); // Initialize all pixels to 'off'
  pinMode(LED_PIN , OUTPUT);  //definir pin como salida
}

void loop()
{
  controlTestLed();
  fauxmo.handle();
}


boolean wifiSetup() {
  // Let us connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(".......");
  Serial.println("WiFi Connected....IP Address:");
  Serial.println(WiFi.localIP());

  return true;
}

void controlTestLed()
{
  digitalWrite(LED_PIN , HIGH);   // poner el Pin en HIGH
  delay(1000);                   // esperar un segundo
  digitalWrite(LED_PIN , LOW);    // poner el Pin en LOW
  delay(1000);
}


void turnOffStrip() {
  strip.fill();
  strip.show();
}
