#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
 #define BLYNK_PRINT Serial
#define sensorTrigPin    12
#define sensorEchoPin    13
/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#include <NewPing.h>
#include <FS.h>
#include <ESP8266HTTPClient.h>
// Set WiFi credentials
#define WIFI_SSID "Wildcats"
#define WIFI_PASS "ENE0T6YB8H7"
 
// Create a new web server
ESP8266WebServer webserver(80);
NewPing sonar = NewPing(12, 13, 400);
String sliters="0";
String dubs;
int cunt =0;

// Handle Root
void rootPage() { 
  webserver.send(200, "text/plain", "Working"); 
}

void handleLitres(){
  
  webserver.send(200, "text/plain", sliters);
  
}
void handlep(){
  
  if (webserver.hasArg("plain")== false){ //Check if body received
 
            webserver.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = "Body received:\n";
             message += webserver.arg("plain");
             message += "\n";
 
      webserver.send(200, "text/plain", message);
      Serial.println(message);
  
}
// Handle 404
void notfoundPage(){ 
  webserver.send(404, "text/plain", "404: Not found"); 
}
 
void setup()
{
  // Setup serial port
  Serial.begin(9600);
  Serial.println();
   if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  File f = SPIFFS.open("/test.html", "w");
  if (!f) {
    Serial.println("file creation failed");
  }
  f.println("<h1>Hello!</h1>");
  f.close();
  //Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(100); }
 
  // WiFi Connected
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
  // Start Web Server
  webserver.on("/", rootPage);
  webserver.on("/h", []() {
    webserver.send(200, "text/plain", "this works as well");
  });
  webserver.on("/p", handlep);
  webserver.on("/litres", handleLitres);
  webserver.onNotFound(notfoundPage);
  webserver.begin();
 
}
 
// Listen for HTTP requests
void loop(void){ 
  float levelp=0;
  float delta_distance=0;
  float wliters=0;
  float wla=0;
  float levelpa=0;
  float delta_distance_a=0;


  
  
  delta_distance=(167-sonar.ping_cm());
  delta_distance_a=(174.6-sonar.ping_cm());
  if(delta_distance < 0)
  {
    delta_distance=0;
  }
  levelp=(delta_distance/167)*100;
  levelpa=delta_distance_a*100/174.5;
  //wliters=levelp*26.07*2;
  wliters = 3500;
  wla=levelpa*27*2;
  sliters = String(wliters,1);
  webserver.handleClient();
  cunt = cunt+1;
  if( cunt == 5)
  {
    
  }
  

  
  
  
   
}
