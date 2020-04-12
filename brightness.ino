

void manageBrightness(int target)
{

     target = target > 100 ? 100 : target;
     target = target < 2 ? 2 : target;
     int diff = brightness > target ? -1 : 1;
     for (int i = brightness + diff; brightness != target; i += diff)
     {
          brightness = i;
          setLedColor(color);
          delay(10);
     }
}

void moreBrightness()
{
     manageBrightness(brightness < 10 ? brightness + 2 : brightness + 10);
}
void lessBrightness()
{
     manageBrightness(brightness <= 10 ? brightness - 2 : brightness - 10);
}