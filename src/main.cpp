#include <Arduino.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
  
const char* ssid = "S";
const char* password =  "ggeznore";
  
AsyncWebServer server(80);
  
int fuelPin = 12;
int oxygenPin = 13;
int ignitionPin; //TODO: connect ignition
  
void setup(){
  
  pinMode(fuelPin, OUTPUT);
  digitalWrite(fuelPin, LOW);
  pinMode(oxygenPin, OUTPUT);
  digitalWrite(oxygenPin, LOW);
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());
  
  server.on("/print", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "I am alive!" + String(digitalRead(fuelPin)));
    Serial.println("print yay");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    digitalWrite(oxygenPin, LOW);
    digitalWrite(fuelPin, LOW);
    Serial.println("recieved off command");
  });

  //FUEL
  
  server.on("/fuelOn", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(fuelPin, HIGH);
    Serial.println("recieved FUAL on command");
  });

  server.on("/1secFuelToggle", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(fuelPin)));
    digitalWrite(fuelPin, HIGH);
    delay(1000);
    digitalWrite(fuelPin, LOW);
  });

  //OXYGEN

  server.on("/oxygenOn", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(oxygenPin, HIGH);
    Serial.println("recieved OXYGEN on command");
  });

  server.on("/1secOxygenToggle", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(fuelPin)));
    digitalWrite(oxygenPin, HIGH);
    delay(1000);
    digitalWrite(oxygenPin, LOW);
  });

  //IGNITION

  server.on("/IgnitionOn", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(ignitionPin, HIGH);
    Serial.println("recieved IGNITION on command");
  });

  server.on("/1secOxygenToggle", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(fuelPin)));
    digitalWrite(ignitionPin, HIGH);
    delay(1000);
    digitalWrite(ignitionPin, LOW);
  });


  //Fire

  server.on("/1secGasFlow", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(fuelPin)));
    for (int i = 3; i > 0; i--) {
      Serial.println("Gas Flowing in: " + String(i));
      delay(1000);
    }
    digitalWrite(oxygenPin, HIGH);
    delay(300);
    digitalWrite(fuelPin, HIGH);
    delay(500);
    digitalWrite(fuelPin, LOW);
    delay(200);
    digitalWrite(oxygenPin, LOW);
  });

  server.on("/1secHotFire", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(fuelPin)));
    for (int i = 3; i > 0; i--) {
      Serial.println("Gas Flowing in: " + String(i));
      delay(1000);
    }
    // TRIGGER IGNITION
    delay(1000);
    digitalWrite(oxygenPin, HIGH);
    delay(300);
    digitalWrite(fuelPin, HIGH);
    delay(500);
    digitalWrite(fuelPin, LOW);
    delay(200);
    digitalWrite(oxygenPin, LOW);
    // TURN IGNITION OFF
  });
  
  server.begin();
}
  
void loop(){}