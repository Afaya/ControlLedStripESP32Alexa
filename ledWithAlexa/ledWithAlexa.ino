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
boolean runningStrip = false;

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
          runningStrip = true;
        }
        else
        {
          Serial.println("turn off");
          runningStrip = false;
        }
      }
    });
  }

  strip.begin(); 
  strip.show(); 
  pinMode(LED_PIN , OUTPUT); 
}

void loop()
{
  controlTestLed();
  fauxmo.handle();

  if (runningStrip) {
    Serial.println("turn on strip with multi color");
    controlStrip();
  } else {
    Serial.println("turn off strip from loop");
    turnOffStrip();
  }
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
  digitalWrite(LED_PIN , HIGH);
  delay(1000);                  
  digitalWrite(LED_PIN , LOW);   
  delay(1000);
}

void controlStrip()
{
  int numberOfPins = strip.numPixels();
  for (int red = 0; red < 4; red++) {
    for (int green = 0; green < 4; green++) {
      for (int blue = 0; blue < 4; blue++) {
        for (int pinLed = 0; pinLed < numberOfPins; pinLed++) {
          int redColor = (red * 85);
          int greenColor = (green * 85);
          int blueColor = (blue * 85);
          
          Serial.println("Color: ");
          Serial.print(redColor);
          Serial.print(", ");
          Serial.print(greenColor);
          Serial.print(", ");
          Serial.print(blueColor);
          Serial.print(", ");
          
          strip.setPixelColor(pinLed, strip.Color(redColor, greenColor, blueColor)); 
          strip.show(); 
          delay(100); 
        }
      }
    }
  }
}


void turnOffStrip() {
  strip.fill();
  strip.show();
}
