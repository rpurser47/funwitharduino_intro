// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino/
// This file adapted from Arduino Ethernet Shield Web Server Tutorial 
// http://startingelectronics.com/tutorials/arduino/ethernet-shield-web-server-tutorial/web-server-read-switch-using-AJAX/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

void setup() 
{
  Bridge.begin();

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();

  Serial.begin(9600);

  while(!Serial); // wait for a serial connection 
  Serial.println("Started");
}

void loop()
{
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}

void process(YunClient client)
{
  // read the command
  String command = client.readStringUntil(13);
  Serial.println(command);
  if(command.startsWith("index"))
  {
    sendWebPage(client);
  }
  if(command.startsWith("ajax_data"))
  {
    sendData(client);
  }
}

void sendWebPage(YunClient client)
{
  // send web page - contains JavaScript with AJAX calls
  client.println("Status: 200");
  client.println("Content-type: text/html");
  client.println(); //mandatory blank line

  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Arduino Web Page</title>");
  client.println("<script type=\"text/javascript\">");
  client.println("function getSensorData() {");
  client.println("nocache = \"?nocache=\" + Math.random() * 1000000;");
  client.println("var request = new XMLHttpRequest();");
  client.println("request.onreadystatechange = function() {");
  client.println("if (this.readyState == 4) {");
  client.println("if (this.status == 200) {");
  client.println("if (this.responseText != null) {");
  client.println("var sensordata = JSON.parse(this.responseText);");
  client.println("document.getElementById(\"FSR_txt\").innerHTML = sensordata.FSRVoltage;");
  client.println("}}}}");
  client.println("request.open(\"GET\", \"ajax_data\" + nocache, true);");
  client.println("request.send(null);");
  // This line was added to cause an update every 2 seconda (Yun upsT.
  client.println("setTimeout('getSensorData()', 2000);");    
  client.println("}");
  client.println("</script>");
  client.println("</head>");
  client.println("<body onload=\"getSensorData()\">");
  //client.println("<body>");
  client.println("<h1>Arduino AJAX Sensor Monitor</h1>");
  client.println("<p>FSR: <span id=\"FSR_txt\">Unread</span> Volts</p>");
  client.println("</body>");
  client.println("</html>");
}

void sendData(YunClient client)
{
  // send ajax data
  client.println("Status: 200");
  client.println("Content-type: text/plain");
  client.println(); //mandatory blank line
  client.print("{\"FSRVoltage\":");
  client.print(analogRead(0) * 5.0 / 1024); 
  client.println("}");
}



