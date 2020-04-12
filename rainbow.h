

#include "color.h"
#include "utils.h"

#define RAINBOW_CHANGE_STEPS 50
#define NEXT_PERIOD 5000 //5000

struct rainbow
{
     unsigned char stepIndex = 0;
     uint32_t colors[7] = {0xff0000, 0xff7f00, 0xffff00, 0x00ff00, 0x0000ff, 0x4b0082, 0x9400d3};
     const unsigned char size = (sizeof(this->colors) / sizeof(*this->colors));
     unsigned char index = random(0, this->size);

     RGB getRainbowStepColor()
     {
          RGB nowColor;
          nowColor.loadHEX(this->colors[this->index]);
          unsigned char nextIndex = (this->index + 1) % this->size;

          RGB nextColor;
          nextColor.loadHEX(this->colors[nextIndex]);

          RGB stepColor = getGradientColor(nowColor, nextColor, this->stepIndex / (float)RAINBOW_CHANGE_STEPS);

          return stepColor;
     }

     void changeRainbowColor()
     {
          unsigned char nextIndex = (this->index + 1) % this->size;
          _manageColorRGB(color,getRainbowStepColor());
          nextPeriod = millis() + NEXT_PERIOD;

          this->stepIndex = (this->stepIndex + 1) % (RAINBOW_CHANGE_STEPS + 1);
          if (this->stepIndex == 0)
          {
               this->index = nextIndex;
          }
     }
};
typedef struct rainbow Rainbow;
