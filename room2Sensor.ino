#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


unsigned long timeout;
int sensorone = D1;
int sensortwo = D2;
bool toggle = false;
bool toggle1 = false;
int sensorState =  0;
int count = 0;


#define FIREBASE_HOST "datacontro.firebaseio.com"
#define FIREBASE_AUTH "T4Sj1NzCmvsoClqegpG3VnaT9DLw2FzNKgqXZ0IR"
#define WIFI_SSID "iPad"
#define WIFI_PASSWORD "mimimiml1111111"

void setup() {

  pinMode(sensorone, INPUT);
  pinMode(sensortwo, INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }//loop while
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("room2/UserinRoom",0);
  Firebase.set("room2/toggle1", true);
}
void loop() {
    Firebase.set("room2/UserinRoom", count);
    Firebase.set("room2/toggle1", toggle1);
  
  if (digitalRead(sensorone) == LOW && toggle == false) {
    sensorState = 1 ;
    timeout = millis();
    toggle = true;
  } else if (digitalRead(sensortwo) == LOW && toggle == false) {
    sensorState = 2 ;
    timeout = millis();
    toggle = true;
  }
  Serial.println(sensorState);
  if (sensorState == 1 && digitalRead(sensortwo) == LOW) {
    count++;
    toggle = false;
    toggle1 = false;
    sensorState = 0;
  } else if (sensorState == 2 && digitalRead(sensorone) == LOW) {
    count--;
    toggle = false;
    toggle1 = true;
    sensorState = 0;
  }
  if (millis() - timeout > 5000 && toggle == true) {
    toggle = false;
  }
}



