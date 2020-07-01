#include <ESP8266WiFi.h>
#include "Interactive2.h"
const char* ssid = "PRC4";
const char* pass = "ecom5333";
WiFiServer server(80);
WiFiClient client;

String header; // to store the HTTP request

String GPIO0State = "off";
String GPIO1State = "off";
String GPIO2State = "on";
String Festival = "off";
int i=0;
void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
    
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid,pass);
  WiFi.config(IPAddress(192,168,0,37),IPAddress(192,168,0,1),IPAddress(255,255,255,0));
  while (WiFi.status() != WL_CONNECTED) {delay(500);}
  
  server.begin();
  delay(1000);
  digitalWrite(3, HIGH);
  
}

void loop() 
{
  client = server.available();              // Listen for incoming clients
  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected())              // loop while the client's connected
    {
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n')                      // if the byte is a newline character
        {
          if (currentLine.length() == 0)    // if the current line is blank, that's the end of the client HTTP request
          {
            ProcessRequest();
            SendWebPage(); 
            break; // Break out of the while loop
          }
          else // if you got a newline, then clear currentLine
            currentLine = "";
        }
        else if (c != '\r')   // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
      }
    }
    header = "";// Clear the header variable
    client.stop();// Close the connection
  }
}

void ProcessRequest()
{
 if (header.indexOf("GET /0/on") >= 0)
    {
      GPIO0State = "on";
      digitalWrite(0, HIGH);
    }
 else if (header.indexOf("GET /0/off") >= 0)
    {
      GPIO0State = "off";
      digitalWrite(0, LOW);
    }
 else if (header.indexOf("GET /1/on") >= 0)
    {
      GPIO1State = "on";
      digitalWrite(1,HIGH);
    }
 else if (header.indexOf("GET /1/off") >= 0)
    {
      GPIO1State = "off";
      digitalWrite(1, LOW);
    }
 else if (header.indexOf("GET /2/on") >= 0)
    {
      GPIO2State = "on";
      digitalWrite(2, LOW);
    }
 else if (header.indexOf("GET /2/off") >= 0)
    {
      GPIO2State = "off";
      digitalWrite(2, HIGH);
    }
 else if (header.indexOf("GET /Festival") >= 0)
    {
      Festival = "on";
      GPIO0State = "off";
      GPIO1State = "off";
      GPIO2State = "off";
      digitalWrite(0, LOW);
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      delay(1000);
      LightsSeries();
      GPIO0State = "on";
      GPIO1State = "on";
      digitalWrite(1, HIGH);
      digitalWrite(2, LOW);
    }
    
 else if (header.indexOf("GET /Stop") >= 0)
    {
      Festival = "off";
      GPIO0State = "off";
      GPIO1State = "off";
      GPIO2State = "off";
      digitalWrite(0, LOW);
      digitalWrite(1, LOW);
      digitalWrite(2, HIGH);
    }
 }

void SendWebPage()
{
  if (GPIO0State == "off") 
   TemplatePage.replace("0/off\"><button class=\"button button2\">OFF" , "0/on\"><button class=\"button\">ON");
  else 
   TemplatePage.replace("0/on\"><button class=\"button\">ON" , "0/off\"><button class=\"button button2\">OFF");

  if (GPIO1State == "off")   
    TemplatePage.replace("1/off\"><button class=\"button button2\">OFF" , "1/on\"><button class=\"button\">ON");
  else                      
    TemplatePage.replace("1/on\"><button class=\"button\">ON" , "1/off\"><button class=\"button button2\">OFF");
   
  if (GPIO2State == "off") 
    TemplatePage.replace("2/off\"><button class=\"button button2\">OFF" , "2/on\"><button class=\"button\">ON");
  else                     
    TemplatePage.replace("2/on\"><button class=\"button\">ON" , "2/off\"><button class=\"button button2\">OFF");
  
  if (Festival == "off") 
    TemplatePage.replace("Stop\"><button class=\"button button2\">Stop" , "Festival\"><button class=\"button\">Festival");
  else                     
    TemplatePage.replace("Festival\"><button class=\"button\">Festival" , "Stop\"><button class=\"button button2\">Stop");
  
  
  client.println(TemplatePage);
}
void LightsSeries()
{
for (int i=0;i<5;i++)
  {
      GPIO0State = "off";
      digitalWrite(0, LOW);
      GPIO1State = "on";
      digitalWrite(1, LOW);
      delay(500);
      GPIO1State = "off";
      digitalWrite(1, HIGH);
      GPIO2State = "off";
      digitalWrite(2, LOW);
      delay(500);
      GPIO2State = "on";
      digitalWrite(2, HIGH);
      GPIO0State = "on";
      digitalWrite(0, HIGH);
      delay(500);
  }  
}
