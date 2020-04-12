#ifndef __COLOR_H_
#define __COLOR_H_

struct hsl
{
     int H = 0;
     float S = 0;
     float L = 0;
};
typedef struct hsl HSL;

struct rgb
{
     unsigned char R;
     unsigned char G;
     unsigned char B;

     void loadHEX(uint32_t color)
     {

          this->R = (color & 0xFF0000) >> 16;
          this->G = (color & 0x00FF00) >> 8;
          this->B = (color & 0x00FF);
     }

     uint32_t getGRB() const
     {
          return (this->R << 8) + (this->G << 16) + this->B;
     }
     uint32_t getRGB() const
     {
          return (this->R << 16) + (this->G << 8) + this->B;
     }

     void print() const
     {
          Serial.println(this->getRGB(), HEX);
     }

     static float Min(float a, float b)
     {
          return a <= b ? a : b;
     }

     static float Max(float a, float b)
     {
          return a >= b ? a : b;
     }

     struct hsl toHSL()
     {
          HSL hsl;

          float r = (this->R / 255.0f);
          float g = (this->G / 255.0f);
          float b = (this->B / 255.0f);

          float min = Min(Min(r, g), b);
          float max = Max(Max(r, g), b);
          float delta = max - min;

          hsl.L = (max + min) / 2;

          if (delta == 0)
          {
               hsl.H = 0;
               hsl.S = 0.0f;
          }
          else
          {
               hsl.S = (hsl.L <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));

               float hue;

               if (r == max)
               {
                    hue = ((g - b) / 6) / delta;
               }
               else if (g == max)
               {
                    hue = (1.0f / 3) + ((b - r) / 6) / delta;
               }
               else
               {
                    hue = (2.0f / 3) + ((r - g) / 6) / delta;
               }

               if (hue < 0)
                    hue += 1;
               if (hue > 1)
                    hue -= 1;

               hsl.H = (int)(hue * 360);
          }

          return hsl;
     }

     static float HueToRGB(float v1, float v2, float vH)
     {
          if (vH < 0)
               vH += 1;

          if (vH > 1)
               vH -= 1;

          if ((6 * vH) < 1)
               return (v1 + (v2 - v1) * 6 * vH);

          if ((2 * vH) < 1)
               return v2;

          if ((3 * vH) < 2)
               return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

          return v1;
     }

     void loadFromHSL(HSL hsl)
     {
          unsigned char r = 0;
          unsigned char g = 0;
          unsigned char b = 0;

          if (hsl.S == 0)
          {
               r = g = b = (unsigned char)(hsl.L * 255);
          }
          else
          {
               float v1, v2;
               float hue = (float)hsl.H / 360;

               v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
               v1 = 2 * hsl.L - v2;

               r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
               g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
               b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
          }
          this->R = r;
          this->G = g;
          this->B = b;
     }
};
typedef struct rgb RGB;

#endif