#include <ESP8266WiFi.h>
#include <espnow.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_MitsubishiHeavy.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>
#include "Nextion.h"

uint8_t broadcastAddress[] = {0x2C, 0xF4, 0x32, 0x1A, 0x7F, 0xAB};

typedef struct struct_message {
  int a;
} struct_message;
struct_message myData;
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

NexPage aircon = NexPage(0, 0, "page0");
NexPage light = NexPage(1, 0, "page1");
NexButton NxPageNext = NexButton(0, 21, "nextbtn");
NexButton NxPageBack = NexButton(1, 6, "backbtn");

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

NexButton NxLightPower = NexButton(1, 1, "lpwr");
NexButton NxLightOn = NexButton(1, 2, "lon");
NexButton NxLightDim = NexButton(1, 3, "ldim");
NexButton NxLightNight = NexButton(1, 4, "lnight");
NexButton NxLightOff = NexButton(1, 5, "loff");
NexPicture NxLSttOn = NexPicture(1, 7, "lstton");
NexPicture NxLSttDim = NexPicture(1, 8, "lsttdim");
NexPicture NxLSttNight = NexPicture(1, 9, "lsttnight");
NexPicture NxLSttOff = NexPicture(1, 10, "lsttoff");

const uint16_t kIrLed = 5;
int temperature = 24;
int fan = 0;
int opmode = 0;
int vertical = 0;
int horizontal = 0;
bool power_state = false;

int light_mode = 0;
bool light_pwr = false;

int page_flag = 0;

// littlefs
bool loadConfig() {
  File configFile = LittleFS.open("/config.json", "r");
  if (!configFile) {
    return false;
  }
  size_t size = configFile.size();
  if (size > 1024) {
    return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonDocument<200> doc;
  auto error = deserializeJson(doc, buf.get());
  if (error) {
    return false;
  }
  temperature = doc["temperature"];
  fan = doc["fan"];
  opmode = doc["opmode"];
  vertical = doc["vertical"];
  horizontal = doc["horizontal"];
  power_state = doc["power_state"];
  light_mode = doc["light_mode"];
  myData.a = doc["light_mode"];
  light_pwr = doc["light_pwr"];
  page_flag = doc["page_flag"];
  return true;
}

bool saveConfig(){
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["fan"] = fan;
  doc["opmode"] = opmode;
  doc["vertical"] = vertical;
  doc["horizontal"] = horizontal;
  doc["power_state"] = power_state;
  doc["light_mode"] = light_mode;
  doc["light_pwr"] = light_pwr;
  doc["page_flag"] = page_flag;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    return false;
  }
  serializeJson(doc, configFile);
  return true;
}

IRMitsubishiHeavy152Ac ac(kIrLed);

NexTouch *nex_listen_list[] = {
    &NxPageNext,
    &NxPageBack,
    &NxPwrBtn,
    &NxTmpUpBtn,
    &NxTmpDwnBtn,
    &NxHorizonBtn,
    &NxVertBtn,
    &NxFanBtn,
    &NxModeBtn,
    &NxLightPower,
    &NxLightOn,
    &NxLightDim,
    &NxLightNight,
    &NxLightOff,
    NULL
};
void set_default() {
  loadConfig();
  ac.setPower(power_state);
  ac.setFan(fan);
  ac.setMode(opmode);
  ac.setTemp(temperature);
  ac.setSwingVertical(vertical);
  ac.setSwingHorizontal(horizontal);
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
  saveConfig();  
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
  saveConfig();
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
  saveConfig();  
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
  saveConfig();  
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
  saveConfig();
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
  saveConfig();  
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
  saveConfig();  
}
/*
 * LIGHT ZONE
 */
void next_page(void *ptr) {
  light.show();
  get_light_state();
  page_flag = 1;
}
void back_page(void *ptr) {
  aircon.show();
  get_state();
  page_flag = 0;
}
void light_power(void *ptr) {
  get_light_state();
  if(light_pwr == false) {
    myData.a = 1;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    light_pwr = true;
    setLightIcon(light_mode);
    get_light_state();
  } else if(light_pwr == true) {
    myData.a = 0;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    light_pwr = false;
    setLightIcon(light_mode);
    get_light_state();
  }
  saveConfig();
}
void light_on(void *ptr) {
  get_light_state();
  myData.a = 1;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  light_pwr = 1;
  setLightIcon(light_mode);
  get_light_state();
  saveConfig();
}
void light_off(void *ptr) {
  get_light_state();
  myData.a = 0;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  light_pwr = 0;
  setLightIcon(light_mode);
  get_light_state();
  saveConfig();
}
void dim_light(void *ptr) {
  get_light_state();
  myData.a = 2;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  light_pwr = 1;
  setLightIcon(light_mode);
  get_light_state();
  saveConfig();
}
void night_light(void *ptr) {
  get_light_state();
  myData.a = 3;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  light_pwr = 1;
  setLightIcon(light_mode);
  get_light_state();
  saveConfig();
}
void get_light_state() {
  light_mode = myData.a;
  setLightIcon(light_mode);
  setLightPower(light_pwr);
}
void setLightPower(bool light_pwr) {
  if(light_pwr == 0){
    NxLightPower.Set_background_image_pic(55);
  } else if(light_pwr == 1){
    NxLightPower.Set_background_image_pic(54);
  }
}
void setLightIcon(int light_mode) {
  if(light_mode == 0) {
    NxLSttOn.setPic(60);
    NxLSttDim.setPic(59);
    NxLSttNight.setPic(58);
    NxLSttOff.setPic(62);
  } else if(light_mode == 1) {
    NxLSttDim.setPic(59);
    NxLSttNight.setPic(58);
    NxLSttOff.setPic(61);
    NxLSttOn.setPic(64);
  } else if(light_mode == 2) {
    NxLSttOn.setPic(60);
    NxLSttNight.setPic(58);
    NxLSttOff.setPic(61);
    NxLSttDim.setPic(63);
  } else if(light_mode == 3) {
    NxLSttOn.setPic(60);
    NxLSttDim.setPic(59);
    NxLSttOff.setPic(61);
    NxLSttNight.setPic(57);
  }
}

void setup() {
  Serial.begin(2000000);
  if (!LittleFS.begin()) {
    return;
  }
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
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
  NxPageNext.attachPop(next_page, &NxPageNext);
  NxPageBack.attachPop(back_page, &NxPageBack);
  NxLightPower.attachPop(light_power, &NxLightPower);
  NxLightOn.attachPop(light_on, &NxLightOn);
  NxLightDim.attachPop(dim_light, &NxLightDim);
  NxLightNight.attachPop(night_light, &NxLightNight);
  NxLightOff.attachPop(light_off, &NxLightOff);
  get_light_state();
  get_state();
  if(page_flag == 0) {
    aircon.show();
    get_state();
  } else if(page_flag == 1) {
    light.show();
    get_light_state();
  }
}

void loop() {
  nexLoop(nex_listen_list);
  if(millis() > 3600000){
    saveConfig();
    ESP.restart();
  }
}
