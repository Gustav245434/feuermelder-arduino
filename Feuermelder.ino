#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* netzwerkname = "Oida";
const char* passwort = "nicostinkt";

void nachrichtWhatsapp(String message){

  String url = "https://api.callmebot.com/whatsapp.php?phone=+4367761486046&apikey=7869418&text=" + urlEncode(message);  
    
  HTTPClient http;
  http.begin(url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST(url);
  
  http.end();
}

void setup() {

  pinMode(23, OUTPUT);
  pinMode(19, INPUT);
  digitalWrite(23, LOW);
  
  Serial.begin(115200);

  WiFi.begin(netzwerkname, passwort);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

const int GPIO22 = 22;

void loop() {

  pinMode(19, INPUT);
  pinMode(23, OUTPUT);
  pinMode(21, OUTPUT);

  if(digitalRead(22) == LOW) {
    Serial.print("HIGH");
    nachrichtWhatsapp("Feueralarm");
    soundAlarm();
    delay(5000);
  } 
  delay(100);
  
}

void soundAlarm() {

  int wiederholungen = 30;

  while(wiederholungen > 0) {

    if(digitalRead(19) == HIGH) {
      Serial.println("Knopf gedrückt. Alarm abgeschalten!");
      return;
    }
  
    digitalWrite(23, HIGH);
    digitalWrite(21, HIGH);
    delay(800);
    digitalWrite(23, LOW);
    digitalWrite(21, LOW);
    delay(800);

    wiederholungen--;
  }
}
