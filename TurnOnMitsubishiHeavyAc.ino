#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_MitsubishiHeavy.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "index.h" 
#include "resource.h"

const uint16_t kIrLed = 4;
const char* ssid = "YOUR-WIFI-SSID";
const char* password = "YOUR-WIFI-PASSWORD";

int temperature, fan, opmode, vertical, horizontal;
bool power_state;

IRMitsubishiHeavy152Ac ac(kIrLed);
ESP8266WebServer server(80);

//================IR function================
void printState() {
  Serial.println("Mitsubishi Heavy A/C remote is in the following state:");
  Serial.printf("%s\n", ac.toString().c_str());
  unsigned char* ir_code = ac.getRaw(); //ac.get__().c_str(); 
  Serial.print("IR Code: 0x");
  for (uint8_t i = 0; i < kMitsubishiHeavy152StateLength; i++)
    Serial.printf("%02X", ir_code[i]);
  Serial.println();
}
void set_default() {
  ac.setPower(false);
  ac.setFan(0);
  ac.setMode(0);
  ac.setTemp(24);
  ac.setSwingVertical(0);
  ac.setSwingHorizontal(0);
}
void get_state() {
  temperature = ac.getTemp();
  opmode = ac.getMode();
  power_state = ac.getPower();
  fan = ac.getFan();
  vertical = ac.getSwingVertical();
  horizontal = ac.getSwingHorizontal();
}
void power_onoff() {
  get_state();
  if(power_state == false) {
    power_state = true;
    ac.setPower(power_state);
    ac.send();
    printState();
  } else if(power_state == true) {
    power_state = false;
    ac.setPower(power_state);
    ac.send();
    printState();
  }
}
void temp_up() {
  get_state();
  if(temperature >= 17 && temperature <31) {
    temperature ++;
    ac.setTemp(temperature);
    ac.send();
    printState();
  } else if(temperature == 31) {
    temperature = 31;
    ac.setTemp(temperature);
    ac.send();
    printState();
  }
}
void temp_down() {
  get_state();
  if(temperature > 17 && temperature <= 31) {
    temperature --;
    ac.setTemp(temperature);
    ac.send();
    printState();
  } else if(temperature == 17) {
    temperature = 17;
    ac.setTemp(temperature);
    ac.send();
    printState();
  }
}
void change_mode() {
  get_state();
  if(opmode >= 0 && opmode < 4) {
    opmode ++;
    ac.setMode(opmode);
    ac.send();
    printState();
  } else if(opmode == 4) {
    opmode = 0;
    ac.setMode(opmode);
    ac.send();
    printState();
  }
}
void change_fan() {
  get_state();
  if(fan >= 0 && fan < 4) {
    fan ++;
    ac.setFan(fan);
    ac.send();
    printState();
  } else if(fan == 4) {
    fan = 6;
    ac.setFan(fan);
    ac.send();
    printState();
  } else if(fan == 6) {
    fan = 8;
    ac.setFan(fan);
    ac.send();
    printState();
  } else if(fan == 8) {
    fan = 0;
    ac.setFan(fan);
    ac.send();
    printState();
  }
}
void change_vertical() {
  get_state();
  if(vertical >= 0 && vertical < 6) {
    vertical ++;
    ac.setSwingVertical(vertical);
    ac.send();
    printState();
  } else if(vertical == 6) {
    vertical = 0;
    ac.setSwingVertical(vertical);
    ac.send();
    printState();
  }
}
void change_horizontal() {
  get_state();
  if(horizontal >= 0 && horizontal < 8) {
    horizontal ++;
    ac.setSwingHorizontal(horizontal);
    ac.send();
    printState();
  } else if(horizontal == 8) {
    horizontal = 0;
    ac.setSwingHorizontal(horizontal);
    ac.send();
    printState();
  }
}
void handleRoot() {
 String s = MAIN_page;
 server.send(200, "text/html", s);
}
void handleStylesCss() {server.send_P(200,"text/css",styles_css);}
void handleMdbCss(){server.send_P(200,"text/css",mdb_css);}
void handleMdbJs() {server.send_P(200,"application/js",mdb_js);}
void handlejQuery() {server.send_P(200,"application/js",jquery);}
void handleFrame(){server.send_P(200,"image/png",frame,sizeof(frame));}
void handleFont1() {server.send_P(200,"font/woff2",DSEG7Classic_Regular,sizeof(DSEG7Classic_Regular));}
void handleFont2() {server.send_P(200,"font/woff2",fa_brands_400,sizeof(fa_brands_400));}
void handleFont3() {server.send_P(200,"font/woff2",fa_regular_400,sizeof(fa_regular_400));}
void handleFont4() {server.send_P(200,"font/woff2",fa_solid_900,sizeof(fa_solid_900));}
void handleFont5() {server.send_P(200,"font/woff2",fontawesome_webfont,sizeof(fontawesome_webfont));}

void setup(void){
  Serial.begin(115200);
  ac.begin();
  set_default();
  Serial.println("Mitsubishi Heavy A/C remote is in the following state:");
  printState();
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/bootstrap.min.js", handleMdbJs);
  server.on("/jquery.js", handlejQuery);
  server.on("/bootstrap.min.css", handleMdbCss);
  server.on("/styles.css", handleStylesCss);
  server.on("/frame.png", handleFrame);
  server.on("/DSEG7Classic-Regular.woff2", handleFont1);
  server.on("/fa-brands-400.woff2", handleFont2);
  server.on("/fa-regular-400.woff2", handleFont3);
  server.on("/fa-solid-900.woff2", handleFont4);
  server.on("/fontawesome-webfont.woff2", handleFont5);
  server.on("/powerBtn", [](){power_onoff();handleRoot();});
  server.on("/modeBtn", [](){change_mode();handleRoot();});
  server.on("/upBtn", [](){temp_up();handleRoot();});
  server.on("/downBtn", [](){temp_down();handleRoot();});
  server.on("/fanBtn", [](){change_fan();handleRoot();});
  server.on("/vertBtn", [](){change_vertical();handleRoot();});
  server.on("/horizonBtn", [](){change_horizontal();handleRoot();});
  
  server.on("/state", HTTP_GET, []() {
    DynamicJsonDocument root(1024);
    get_state();
    root["mode"] = opmode;
    root["fan"] = fan;
    root["temp"] = temperature;
    root["power"] = power_state;
    root["vert"] = vertical;
    root["horizon"] = horizontal;
    String output;
    serializeJson(root, output);
    server.send(200, "text/plain", output);
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
