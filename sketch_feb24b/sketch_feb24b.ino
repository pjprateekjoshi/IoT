#include <ESP8266WiFi.h>

WiFiServer server(80);
void setup(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Hello_Prateek","qqqqqqwq");
  server.begin();

  Serial.begin(9600);
  IPAddress HTTPS_ServerIP=WiFi.softAPIP();
  Serial.print("Serial IP is: ");
  Serial.println(HTTPS_ServerIP);
}

void loop(){
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("Somebody has connected :)");
  String request = client.readString();

  Serial.println(request);
}

