// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino/
// Copyright Rob Purser, 2013

#include <Bridge.h>
#include <HttpClient.h>

void setup()
{
  Bridge.begin();
  Serial.begin(9600);
  while(!Serial); // wait for a serial connection 
}

void loop()
{
  HttpClient client;

  // Make a HTTP request:
  client.get("http://www.timeapi.org/edt/now");

  // if there are incoming bytes available 
  // from the server, read them and print them:  
  while (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
  Serial.println();
  Serial.flush();

  delay(5000);
}

