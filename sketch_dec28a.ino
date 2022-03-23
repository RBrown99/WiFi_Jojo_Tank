#include <ESP8266mDNS.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 #define BLYNK_PRINT Serial
#define sensorTrigPin    12
#define sensorEchoPin    13
/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#include <NewPing.h>
// Set WiFi credentials

#define APSSID "WLMSetUp"
#define APPSK  "123456789"
// Create a new web server
ESP8266WebServer webserver(80);
ESP8266WebServer startserver(80);
NewPing sonar = NewPing(12, 13, 400);
String sliters="0";
String WIFI_SSID = "xxxx";
String WIFI_PASS = "xxxx";
String tsid = "xxxx";
String tspa = "xxxx";
const char *ssid = APSSID;
const char *password = APPSK;
bool setupcheck = false;
// Handle Root
void rootPage() { 
  webserver.send(200, "text/plain", "Working"); 
}

void handleLitres(){
  webserver.send(200, "text/plain", sliters);
}
// Handle 404
void notfoundPage(){ 
  webserver.send(404, "text/plain", "404: Not found"); 
}
void rootPageStart() { 
  startserver.send(200, "text/html", "<h1>You are connected</h1>");
}
void StartIP() { 
  
  if (startserver.hasArg("plain")== false){ //Check if body received
 
            startserver.send(200, "text/plain", "Body not received");
            tsid ="xxxx";
            return;
 
      }
      String message = "Body received:\n";
             message += startserver.arg("plain");
             message += "\n";
 tsid = startserver.arg("plain");
      startserver.send(200, "text/plain", message);
      Serial.println(message);
 
      
}
void StartPass() { 
   if (startserver.hasArg("plain")== false){ //Check if body received
 
            startserver.send(200, "text/plain", "Body not received");
            tspa = "xxxx";
            return;
 
      }
        String message = "Body received:\n";
             message += startserver.arg("plain");
             message += "\n";
 tspa = startserver.arg("plain");
      startserver.send(200, "text/plain", message);
      Serial.println(message);
      
 
      
}
 
void setup()
{
  // Setup serial port
  Serial.begin(9600);
  Serial.println();
  
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  startserver.on("/", rootPageStart);
  startserver.on("/ip", StartIP);
  startserver.on("/pass", StartPass);
  startserver.begin();
  Serial.println("HTTP server started");
  
 
  
 
}
 
// Listen for HTTP requests
void loop(void){ 
  if(setupcheck==false)
  {
    startserver.handleClient();
    WIFI_SSID = tsid;
    WIFI_PASS = tspa;
  }
  if((WIFI_SSID != "xxxx")&&(WIFI_PASS != "xxxx")&&(setupcheck==false))
  {
// startserver.close;
  startserver.stop();
  WiFi.softAPdisconnect(true);
//Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(100); }
 
  // WiFi Connected
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 if(MDNS.begin("myesp"))
 {
  
  Serial.println("mDNS Started");
 }
    // Start Web Server
  webserver.on("/", rootPage);
  webserver.on("/h", []() {
    webserver.send(200, "text/plain", "this works as well");
  });
  webserver.on("/p", []() {
    webserver.send(200, "text/plain", "p");
  });
  webserver.on("/litres", handleLitres);
  webserver.onNotFound(notfoundPage);
  webserver.begin();

  setupcheck=true;
  }
  if(setupcheck == true)
  {
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
  wliters=levelp*26.07*2;
  wla=levelpa*27*2;
  //sliters = String(wliters,1);
  sliters = "9088";
  webserver.handleClient();
  MDNS.update();


  
  
  }
}
