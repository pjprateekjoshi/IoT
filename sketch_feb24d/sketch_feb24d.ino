#include <ESP8266WiFi.h>

WiFiServer server(80);
int LED_PIN=16;
void setup(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Hello_Prateek","qqqqqqwq");
  server.begin();

  Serial.begin(9600);
  IPAddress HTTPS_ServerIP=WiFi.softAPIP();
  Serial.print("Serial IP is: ");
  Serial.println(HTTPS_ServerIP);

  pinMode (LED_PIN, OUTPUT);
  digitalWrite (LED_PIN, LOW);
}

void loop(){
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("Somebody has connected :)");
  String request = client.readString();

  Serial.println(request);

  if (request.indexOf("/OFF") != -1)
  {
    digitalWrite (LED_PIN, HIGH);
  }else if(request.indexOf("/ON") != -1)
  {
      digitalWrite (LED_PIN, LOW);
  }

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE html><html><head><title>LED control</title></head><body><br><br><button onclick=\"location.href='/ON'\">LED ON</button><br><br><br><button onclick=\"location.href='/OFF'\">LED OFF</button></body></html>";

  client.flush();
  client.println(s);
  delay(1);
  Serial.println("Client disconnected");
}

