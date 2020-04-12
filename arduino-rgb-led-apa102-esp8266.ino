
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ThingerESP8266.h>
#include "rainbow.h"

//Thinger.io
#define USERNAME "************"
#define DEVICE_ID "************"
#define DEVICE_CREDENTIAL "************"
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define SSID "*******************"
#define SSID_PASSWORD "*******************"
#define serialRate 115200       // use 115200 for ftdi based boards
#define COLOR_IN_MILLIS 7200000 //1800000 = 30min

//Global Vars

Rainbow rainbow;

char ledsState = 1;
void switchLeds(char state)
{
     ledsState = state;

     if (state == 0)
     {
          RGB color;
          color.R = 0;
          color.G = 0;
          color.B = 0;
          manageColorRGB(color);
     }
}

void setup()
{
     Serial.begin(serialRate);
     randomSeed(analogRead(0));
     strip.begin();
     strip.show();

     thing.add_wifi(SSID, SSID_PASSWORD);

     thing["color"] >> [](pson &out) {
          char colorHex[10];
          sprintf(colorHex, "%X", color.getRGB());
          out = String(colorHex);
     };

     thing["brightness"] >> [](pson &out) {
          out = brightness;
     };

     thing["hours"] >> [](pson &out) {
          out = millis() / float(1000 * 60 * 60);
     };
     thing["millis"] >> [](pson &out) {
          out = millis();
     };
     thing["red"] << [](pson &in) {
          manageColorIndex(0, in);
     };
     thing["orange"] << [](pson &in) {
          manageColorIndex(1, in);
     };
     thing["yellow"] << [](pson &in) {
          manageColorIndex(2, in);
     };
     thing["green"] << [](pson &in) {
          manageColorIndex(3, in);
     };
     thing["blue"] << [](pson &in) {
          manageColorIndex(4, in);
     };
     thing["indigo"] << [](pson &in) {
          manageColorIndex(5, in);
     };
     thing["violet"] << [](pson &in) {
          manageColorIndex(6, in);
     };
     thing["rainbow"] << [](pson &in) {
          if (!in.is_empty())
          {
               rainbow.changeRainbowColor();
          };
     };
     thing["switch-on"] << [](pson &in) {
          if (!in.is_empty())
          {
               switchLeds(1);
               rainbow.changeRainbowColor();
          };
     };

     thing["switch-off"] << [](pson &in) {
          if (!in.is_empty())
          {
               switchLeds(0);
          };
     };
     thing["switch"] << [](pson &in) {
          if (!in.is_empty())
          {
               switchLeds(!ledsState);
          };
     };

     thing["more-brightness"] << [](pson &in) {
          if (!in.is_empty())
          {
               moreBrightness();
          }
     };
     thing["less-brightness"] << [](pson &in) {
          if (!in.is_empty())
          {
               lessBrightness();
          }
     };

     thing["command"] << [](pson &request) {
          if (!request.is_empty())
          {
               String setScene = request["setScene"];
               String powerState = request["powerState"];
               String endpointId = request["endpointId"];
               int percentageState = request["brightness"];
               HSL hsl;
               hsl.H = request["color"]["hue"];
               hsl.S = request["color"]["saturation"];
               hsl.L = request["color"]["brightness"];
               hsl.L = hsl.L * 0.5;

               if (endpointId == "a2-light-v3-lamparita")
               {
                    if (powerState == "ON")
                    {
                         switchSonoff(1);
                    }
                    else if (powerState == "OFF")
                    {
                         switchSonoff(0);
                    }
               }
               else
               {
                    if (powerState == "OFF")
                    {
                         switchLeds(0);
                    }
                    else
                    {
                         switchLeds(1);
                         if (percentageState > 0)
                         {
                              manageBrightness(percentageState);
                         }
                         //Scenes
                         if (setScene == "Activate") //set scene color
                         {
                              rainbow.index = random(0, rainbow.size);
                              rainbow.changeRainbowColor();
                         }
                         else if (setScene == "SetColor") //set static color
                         {
                              if (hsl.L > 0)
                              {
                                   manageColorHSL(hsl);
                              }
                         }
                    }
               }
          };
     };
}

void loop()
{

     if (millis() > nextPeriod)
     {
          rainbow.changeRainbowColor();
     }

     thing.handle();

     delay(NEXT_PERIOD < 250 ? NEXT_PERIOD : 250);
}
