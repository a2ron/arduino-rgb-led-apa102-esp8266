

int getSonoffState()
{
     HTTPClient http;
     http.begin("http://<user>:<pass>@<host>/ay");
     int httpCode = http.GET();
     String payload = http.getString(); //Get the request response payload
     http.end();                        //Close connection
     int state = 0;
     if (payload.indexOf("ON") >= 0)
     {
          state = 1; 
     }
     return state;
}

void _switchSonoff()
{
     HTTPClient http;
     http.begin("http://<user>:<pass>@<host>/ay?o=1");
     int httpCode = http.GET();
     http.end();
}

void switchSonoff(int state)
{
     int lampState = getSonoffState();
     if ((lampState == 1 && state == 0) || (lampState == 0 && state == 1))
     {
          _switchSonoff();
     }
}
