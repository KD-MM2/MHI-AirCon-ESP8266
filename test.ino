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
#include "Nextion.h"

NexButton NxPwrBtn = NexButton(0, 1, "pwrbtn");
NexButton NxTmpUpBtn = NexButton(0, 2, "tmpup");
NexButton NxTmpDwnBtn = NexButton(0, 3, "tmpdown");
NexButton NxHorizonBtn = NexButton(0, 4, "horizon");
NexButton NxVertBtn = NexButton(0, 5, "vert");
NexButton NxFanBtn = NexButton(0, 6, "fanbtn");
NexButton NxModeBtn = NexButton(0, 7, "modebtn");
NexNumber NxTemp = NexNumber(0, 20, "temp");

NexPicture NxMAuto = NexPicture(0, 11, "auto");
NexPicture NxMCool = NexPicture(0, 12, "cool");
NexPicture NxMDry = NexPicture(0, 13, "dry");
NexPicture NxMFan = NexPicture(0, 14, "mfan");
NexPicture NxMHeat = NexPicture(0, 15, "heat");

NexPicture NxFan = NexPicture(0, 10, "fan");
NexPicture NxFanMAuto = NexPicture(0, 16, "fauto");
NexPicture NxFanMMax = NexPicture(0, 17, "fmax");
NexPicture NxFanMTurbo = NexPicture(0, 18, "fturbo");
NexPicture NxFanMEco = NexPicture(0, 19, "feco");

NexPicture NxVert = NexPicture(0, 8, "vertical");
NexPicture NxHorizon = NexPicture(0, 9, "horizontal");

const uint16_t kIrLed = 15;
const char* ssid = "YOUR-WIFI-SSID";
const char* password = "YOUR-WIFI-PASSWORD";
int temperature, fan, opmode, vertical, horizontal;
bool power_state;

IRMitsubishiHeavy152Ac ac(kIrLed);
ESP8266WebServer server(80);

NexTouch *nex_listen_list[] = {
    &NxPwrBtn,
    &NxTmpUpBtn,
    &NxTmpDwnBtn,
    &NxHorizonBtn,
    &NxVertBtn,
    &NxFanBtn,
    &NxModeBtn,
    NULL
};

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
  NxTemp.setValue(temperature);
  setPwrBtnIcon(power_state);
  setModeIcon(opmode);
  setFanIcon(fan);
  setVertIcon(vertical);
  setHorizonIcon(horizontal);
}
void setPwrBtnIcon(bool power_state){
  if(power_state == 0){
    NxPwrBtn.Set_background_image_pic(55);
  } else if(power_state == 1){
    NxPwrBtn.Set_background_image_pic(54);
  }
}
void setHorizonIcon(int horizontal){
  if(horizontal == 0){
    NxHorizon.setPic(23);
  } else if(horizontal == 1) {
    NxHorizon.setPic(24);
  } else if(horizontal == 2) {
    NxHorizon.setPic(25);
  } else if(horizontal == 3) {
    NxHorizon.setPic(26);
  } else if(horizontal == 4) {
    NxHorizon.setPic(27);
  } else if(horizontal == 5) {
    NxHorizon.setPic(28);
  } else if(horizontal == 6) {
    NxHorizon.setPic(29);
  } else if(horizontal == 7) {
    NxHorizon.setPic(30);
  } else if(horizontal == 8) {
    NxHorizon.setPic(31);
  }
}
void setVertIcon(int vertical){
  if(vertical == 0){
    NxVert.setPic(32);
  } else if(vertical == 1){
    NxVert.setPic(33);
  } else if(vertical == 2){
    NxVert.setPic(34);
  } else if(vertical == 3){
    NxVert.setPic(35);
  } else if(vertical == 4){
    NxVert.setPic(36);
  } else if(vertical == 5){
    NxVert.setPic(37);
  } else if(vertical == 6){
    NxVert.setPic(38);
  }
}
void setFanIcon(int fan){
  if(fan == 0){
    NxFan.setPic(53);
    NxFanMAuto.setPic(16);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if(fan == 4){
    NxFan.setPic(49);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(18);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if(fan == 6){
    NxFan.setPic(53);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(22);
  } else if(fan == 8){
    NxFan.setPic(49);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(20);
    NxFanMEco.setPic(21);
  } else if(fan == 1){
    NxFan.setPic(52);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if(fan == 2){
    NxFan.setPic(51);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if(fan == 3){
    NxFan.setPic(50);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  }
}
void setModeIcon(int opmode){
  if(opmode == 0){
    NxMAuto.setPic(40);
    NxMCool.setPic(41);
    NxMDry.setPic(43);
    NxMFan.setPic(45);
    NxMHeat.setPic(47);
  } else if(opmode == 1){
    NxMAuto.setPic(39);
    NxMCool.setPic(42);
    NxMDry.setPic(43);
    NxMFan.setPic(45);
    NxMHeat.setPic(47);
  } else if(opmode == 2){
    NxMAuto.setPic(39);
    NxMCool.setPic(41);
    NxMDry.setPic(44);
    NxMFan.setPic(45);
    NxMHeat.setPic(47);
  } else if(opmode == 3){
    NxMAuto.setPic(39);
    NxMCool.setPic(41);
    NxMDry.setPic(43);
    NxMFan.setPic(46);
    NxMHeat.setPic(47);
  } else if(opmode == 4){
    NxMAuto.setPic(39);
    NxMCool.setPic(41);
    NxMDry.setPic(43);
    NxMFan.setPic(45);
    NxMHeat.setPic(48);
  }
}
void power_onoff(void *ptr) {
  get_state();
  if(power_state == false) {
    power_state = true;
    ac.setPower(power_state);
    setPwrBtnIcon(power_state);
    ac.send();
  } else if(power_state == true) {
    power_state = false;
    ac.setPower(power_state);
    setPwrBtnIcon(power_state);
    ac.send();
  }
}
void temp_up(void *ptr) {
  get_state();
  if(temperature >= 17 && temperature <31) {
    temperature ++;
    ac.setTemp(temperature);
    NxTemp.setValue(temperature);
    ac.send();
  } else if(temperature == 31) {
    temperature = 31;
    ac.setTemp(temperature);
    NxTemp.setValue(temperature);
    ac.send();
  }
}
void temp_down(void *ptr) {
  get_state();
  if(temperature > 17 && temperature <= 31) {
    temperature --;
    ac.setTemp(temperature);
    NxTemp.setValue(temperature);
    ac.send();
  } else if(temperature == 17) {
    temperature = 17;
    ac.setTemp(temperature);
    NxTemp.setValue(temperature);
    ac.send();  
  }
}
void change_mode(void *ptr) {
  get_state();
  if(opmode >= 0 && opmode < 4) {
    opmode ++;
    ac.setMode(opmode);
    setModeIcon(opmode);
    ac.send();
  } else if(opmode == 4) {
    opmode = 0;
    ac.setMode(opmode);
    setModeIcon(opmode);
    ac.send();
  }
}
void change_fan(void *ptr) {
  get_state();
  if(fan >= 0 && fan < 4) {
    fan ++;
    ac.setFan(fan);
    setFanIcon(fan);
    ac.send();
  } else if(fan == 4) {
    fan = 8;
    ac.setFan(fan);
    setFanIcon(fan);
    ac.send();
  } else if(fan == 8) {
    fan = 6;
    ac.setFan(fan);
    setFanIcon(fan);
    ac.send();
  } else if(fan == 6) {
    fan = 0;
    ac.setFan(fan);
    setFanIcon(fan);
    ac.send();
  }
}
void change_vertical(void *ptr) {
  get_state();
  if(vertical >= 0 && vertical < 6) {
    vertical ++;
    ac.setSwingVertical(vertical);
    setVertIcon(vertical);
    ac.send();
  } else if(vertical == 6) {
    vertical = 0;
    ac.setSwingVertical(vertical);
    setVertIcon(vertical);
    ac.send();
  }
}
void change_horizontal(void *ptr) {
  get_state();
  if(horizontal >= 0 && horizontal < 8) {
    horizontal ++;
    ac.setSwingHorizontal(horizontal);
    setHorizonIcon(horizontal);
    ac.send();
  } else if(horizontal == 8) {
    horizontal = 0;
    ac.setSwingHorizontal(horizontal);
    setHorizonIcon(horizontal);
    ac.send();
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
  nexInit();
  NxPwrBtn.attachPop(power_onoff, &NxPwrBtn);
  NxTmpUpBtn.attachPop(temp_up, &NxTmpUpBtn);
  NxTmpDwnBtn.attachPop(temp_down, &NxTmpDwnBtn);
  NxHorizonBtn.attachPop(change_horizontal, &NxHorizonBtn);
  NxVertBtn.attachPop(change_vertical, &NxVertBtn);
  NxFanBtn.attachPop(change_fan, &NxFanBtn);
  NxModeBtn.attachPop(change_mode, &NxModeBtn);
  get_state();
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
    
  // wip
  server.on("/powerBtn", [](){
      power_onoff(void *ptr);
      handleRoot();
  });
  server.on("/modeBtn", [](){
      change_mode(void *ptr);
      handleRoot();
  });
  server.on("/upBtn", [](){
      temp_up(void *ptr);
      handleRoot();
  });
  server.on("/downBtn", [](){
      temp_down(void *ptr);
      handleRoot();
  });
  server.on("/fanBtn", [](){
      change_fan(void *ptr);
      handleRoot();
  });
  server.on("/vertBtn", [](){
      change_vertical(void *ptr);
      handleRoot();
  });
  server.on("/horizonBtn", [](){
      change_horizontal(void *ptr);
      handleRoot();
  });
    
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
  nexLoop(nex_listen_list);
  server.handleClient();
}
