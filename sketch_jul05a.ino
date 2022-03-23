





/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define sensorTrigPin    12
#define sensorEchoPin    13
/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#include <NewPing.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "iSk3q7N2ft0nttLtu8aB2ApFNcv_fmAi";
//"2swayFBQKfglEoDDIbeyMYjHm1A42PbB";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WildCats";
char pass[] = "ENE0T6YB8H7";

NewPing sonar = NewPing(12, 13, 400);
void setup()
{
  // Debug console
  Serial.begin(9600);
//pinMode(sensorTrigPin, OUTPUT);
    //pinMode(sensorEchoPin, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{   
  float levelp=0;
  float delta_distance=0;
  float wliters=0;
  float wla=0;
  float levelpa=0;
  float delta_distance_a=0;
  Blynk.run();
  delta_distance=(167-sonar.ping_cm());
  delta_distance_a=(174.6-sonar.ping_cm());
  if(delta_distance < 0)
  {
    delta_distance=0;
  }
  levelp=(delta_distance/167)*100;
  levelpa=delta_distance_a*100/174.5;
  wliters=levelp*26.07*2;
  wla=levelpa*27*2;
  //Serial.print(sonar.ping_cm());
 delay(10); 
  Blynk.virtualWrite(V1,levelp);
  Blynk.virtualWrite(V2,wliters);
  Blynk.virtualWrite(V3,levelpa);
  Blynk.virtualWrite(V4,wla);
}
