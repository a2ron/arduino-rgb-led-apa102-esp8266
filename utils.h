
#include "color.h"

#include <Adafruit_DotStar.h>

#define NUMPIXELS 82
#define DATAPIN D6
#define CLOCKPIN D8
#define CHANGE_STEPS 40

RGB color;
unsigned long int nextPeriod = 0;
int brightness = 20;

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

RGB getGradientColor(RGB from_color, RGB to_color, float percentage)
{

     unsigned char froms[3] = {from_color.R, from_color.G, from_color.B};
     unsigned char tos[3] = {to_color.R, to_color.G, to_color.B};
     unsigned char res[3];

     for (unsigned char i = 0; i < 3; ++i)
     {
          int diff = froms[i] - tos[i];
          res[i] = froms[i] - (percentage * diff);
     }
     RGB color;
     color.R = res[0];
     color.G = res[1];
     color.B = res[2];
     return color;
}

void setLedColor(RGB _color)
{
     color = _color;
     HSL hsl = _color.toHSL();
     hsl.L = hsl.L * float(brightness) / 100;
     _color.loadFromHSL(hsl);
     uint32_t colorGRB = _color.getGRB();
     for (int i = 0; i < NUMPIXELS; ++i)
     {
          strip.setPixelColor(i, colorGRB);
     }
     strip.show();
}

void _manageColorRGB(RGB _fromColor, RGB targetColor)
{
     RGB fromColor;
     fromColor.R = _fromColor.R;
     fromColor.G = _fromColor.G;
     fromColor.B = _fromColor.B;

     for (unsigned char i = 0; i <= CHANGE_STEPS; ++i)
     {
          RGB stepColor = getGradientColor(fromColor, targetColor, float(i) / CHANGE_STEPS);
          setLedColor(stepColor);
          delay(10);
     }
}
