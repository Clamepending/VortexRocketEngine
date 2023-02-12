#include <Arduino.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
  
const char* ssid = "S";
const char* password =  "ggeznore";
  
AsyncWebServer server(80);
  
int relayPin = 33;
  
void setup(){
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());
  
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    digitalWrite(relayPin, LOW);
    Serial.println("recieved off command");
  });
  
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(relayPin, HIGH);
    Serial.println("recieved on command");
  });
  
  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(relayPin, !digitalRead(relayPin));
    Serial.println("recieved toggle command");
  });
  
  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(relayPin)));
  });

  server.on("/print", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(relayPin)));
    Serial.println("print yay");
  });
  
  server.begin();
}
  
void loop(){}