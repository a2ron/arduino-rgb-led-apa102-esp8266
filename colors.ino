
void manageColorIndex(unsigned char _colorIndex, pson &in)

{
     if (!in.is_empty())
     {
          RGB targetColor;
          targetColor.loadHEX(rainbow.colors[_colorIndex]);
          manageColorRGB(targetColor);
     }
}

void manageColorRGB(RGB targetColor)
{
     _manageColorRGB(color,targetColor);
     nextPeriod = millis() + COLOR_IN_MILLIS;

}

void manageColorHSL(HSL hsl)
{
     RGB theColor;
     theColor.loadFromHSL(hsl);
     manageColorRGB(theColor);
}
