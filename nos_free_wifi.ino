#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h> // biblioteca -> https://github.com/dancol90/ESP8266Ping

//wifi
const char* ssid     = "NOS_WIFI_Fon";
const char* password = "";

//nos login captive
const String NOSUSR  = "";
const String NOSPASS  = "";
//gerada aqui -> https://www.grc.com/fingerprints.htm
const String fingerprint  = "E6:E9:08:D6:6A:7E:E7:5D:34:5D:F0:DB:28:14:DA:2B:8D:87:3A:02";



const char* remote_host = "www.google.com";

void setup() {


  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  //nos wifi
  String uri = "";

  static const char* LOCATION = "Location";
  static const char* SET_COOKIE = "Set-Cookie";
  static const char* HEADER_NAMES[] = {LOCATION, SET_COOKIE};

  HTTPClient http;
  // saca o captive portal da nos ja com os querystrings
  http.begin("http://captive.apple.com/");
  http.collectHeaders(HEADER_NAMES, 2);
  int httpCode = http.GET();
  uri = http.header(LOCATION);

  // print do link do captive portal
  Serial.print("portal=");
  Serial.println(uri);
  delay(2000);

  http.begin(uri,fingerprint);     //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
  http.addHeader("Cookie", http.header(SET_COOKIE));
  httpCode = http.POST("userFake=" + NOSUSR + "&UserName=NOS/" + NOSUSR + "&Password=" + NOSPASS); //Send the request
  Serial.println(httpCode);   //Print 302 movido temp -2*/
  delay(2000);


  uri = http.header(LOCATION);
  http.collectHeaders(HEADER_NAMES, 2);
  httpCode = http.GET();
  http.begin(uri);

  Serial.print("1-redirect=");
  Serial.println(uri);
  Serial.println(httpCode);   //Print 302 movido temp -2*/
  delay(2000);


  uri = http.header(LOCATION);
  http.collectHeaders(HEADER_NAMES, 2);
  httpCode = http.GET();
  http.begin(uri);

  Serial.print("2-redirect=");
  Serial.println(uri);
  Serial.println(httpCode);   //Print 302 movido temp -2*/
  delay(2000);

  
  http.end();  //Close connection


  delay(2000);


}



void loop() {


  Serial.print("Pinging host ");
  Serial.println(remote_host);

  if (Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }





}
