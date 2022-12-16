#include <ESP8266WiFi.h>
#include <espnow.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>
#include "Nextion.h"

uint8_t broadcastAddress[] = { 0xBC, 0xFF, 0x4D, 0x18, 0x87, 0x7F };

typedef struct struct_message {
  uint32_t id;
  uint32_t light_mode;
  bool light_pwr;
  uint32_t temperature;
  uint32_t fan;
  uint32_t opmode;
  uint32_t vertical;
  uint32_t horizontal;
  bool power_state;
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  //Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    //Serial.println("Delivery success");
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

// set default values
uint32_t temperature = 24;
uint32_t fan = 0;
uint32_t opmode = 0;
uint32_t vertical = 0;
uint32_t horizontal = 0;
bool power_state = false;

uint32_t light_mode = 0;
bool light_pwr = false;

int page_flag = 0;

// spiffs
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
  StaticJsonDocument<512> doc;
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
  light_pwr = doc["light_pwr"];
  page_flag = doc["page_flag"];
  return true;
  configFile.close();
}

bool saveConfig() {
  StaticJsonDocument<512> doc;
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
  configFile.close();
}

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

// aircon func
void sendDATA() {
  if (page_flag == 0) {
    myData.id = 0;
    myData.temperature = temperature;
    myData.fan = fan;
    myData.opmode = opmode;
    myData.vertical = vertical;
    myData.horizontal = horizontal;
    myData.power_state = power_state;
  } else if (page_flag == 1) {
    myData.id = 1;
    myData.light_mode = light_mode;
    myData.light_pwr = light_pwr;
  }
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  saveConfig();
}

void setPwrBtnIcon(bool power_state) {
  if (power_state == 0) {
    NxPwrBtn.Set_background_image_pic(55);
  } else if (power_state == 1) {
    NxPwrBtn.Set_background_image_pic(54);
  }
}

void setHorizonIcon(int horizontal) {
  if (horizontal == 0) {
    NxHorizon.setPic(23);
  } else if (horizontal == 1) {
    NxHorizon.setPic(24);
  } else if (horizontal == 2) {
    NxHorizon.setPic(25);
  } else if (horizontal == 3) {
    NxHorizon.setPic(26);
  } else if (horizontal == 4) {
    NxHorizon.setPic(27);
  } else if (horizontal == 5) {
    NxHorizon.setPic(28);
  } else if (horizontal == 6) {
    NxHorizon.setPic(29);
  } else if (horizontal == 7) {
    NxHorizon.setPic(30);
  } else if (horizontal == 8) {
    NxHorizon.setPic(31);
  }
}

void setVertIcon(int vertical) {
  if (vertical == 0) {
    NxVert.setPic(32);
  } else if (vertical == 1) {
    NxVert.setPic(33);
  } else if (vertical == 2) {
    NxVert.setPic(34);
  } else if (vertical == 3) {
    NxVert.setPic(35);
  } else if (vertical == 4) {
    NxVert.setPic(36);
  } else if (vertical == 5) {
    NxVert.setPic(37);
  } else if (vertical == 6) {
    NxVert.setPic(38);
  }
}

void setFanIcon(int fan) {
  if (fan == 0) {
    NxFan.setPic(53);
    NxFanMAuto.setPic(16);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if (fan == 4) {
    NxFan.setPic(49);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(18);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if (fan == 6) {
    NxFan.setPic(53);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(22);
  } else if (fan == 8) {
    NxFan.setPic(49);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(20);
    NxFanMEco.setPic(21);
  } else if (fan == 1) {
    NxFan.setPic(52);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if (fan == 2) {
    NxFan.setPic(51);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  } else if (fan == 3) {
    NxFan.setPic(50);
    NxFanMAuto.setPic(15);
    NxFanMMax.setPic(17);
    NxFanMTurbo.setPic(19);
    NxFanMEco.setPic(21);
  }
}

void setModeIcon(int opmode) {
  if (opmode == 0) {
    NxMAuto.setPic(40);
    NxMCool.setPic(41);
    NxMDry.setPic(43);
    NxMFan.setPic(45);
    NxMHeat.setPic(47);
  } else if (opmode == 1) {
    NxMAuto.setPic(39);
    NxMCool.setPic(42);
    NxMDry.setPic(43);
    NxMFan.setPic(45);
    NxMHeat.setPic(47);
  } else if (opmode == 2) {
    NxMAuto.setPic(39);
    NxMCool.setPic(41);
    NxMDry.setPic(44);
    NxMFan.setPic(45);
    NxMHeat.setPic(47);
  } else if (opmode == 3) {
    NxMAuto.setPic(39);
    NxMCool.setPic(41);
    NxMDry.setPic(43);
    NxMFan.setPic(46);
    NxMHeat.setPic(47);
  } else if (opmode == 4) {
    NxMAuto.setPic(39);
    NxMCool.setPic(41);
    NxMDry.setPic(43);
    NxMFan.setPic(45);
    NxMHeat.setPic(48);
  }
}

void power_onoff(void *ptr) {
  if (power_state == false) {
    power_state = true;
    setPwrBtnIcon(power_state);
  } else if (power_state == true) {
    power_state = false;
    setPwrBtnIcon(power_state);
  }
  sendDATA();
}

void temp_up(void *ptr) {
  if (temperature >= 17 && temperature < 31) {
    temperature++;
    NxTemp.setValue(temperature);
  } else if (temperature == 31) {
    temperature = 31;
    NxTemp.setValue(temperature);
  }
  sendDATA();
}

void temp_down(void *ptr) {
  if (temperature > 17 && temperature <= 31) {
    temperature--;
    NxTemp.setValue(temperature);
  } else if (temperature == 17) {
    temperature = 17;
    NxTemp.setValue(temperature);
  }
  sendDATA();
}

void change_mode(void *ptr) {
  if (opmode >= 0 && opmode < 4) {
    opmode++;
    setModeIcon(opmode);
  } else if (opmode == 4) {
    opmode = 0;
    setModeIcon(opmode);
  }
  sendDATA();
}
void change_fan(void *ptr) {
  if (fan >= 0 && fan < 4) {
    fan++;
    setFanIcon(fan);
  } else if (fan == 4) {
    fan = 8;
    setFanIcon(fan);
  } else if (fan == 8) {
    fan = 6;
    setFanIcon(fan);
  } else if (fan == 6) {
    fan = 0;
    setFanIcon(fan);
  }
  sendDATA();
}

void change_vertical(void *ptr) {
  if (vertical >= 0 && vertical < 6) {
    vertical++;
    setVertIcon(vertical);
  } else if (vertical == 6) {
    vertical = 0;
    setVertIcon(vertical);
  }
  sendDATA();
}

void change_horizontal(void *ptr) {
  if (horizontal >= 0 && horizontal < 8) {
    horizontal++;
    setHorizonIcon(horizontal);
  } else if (horizontal == 8) {
    horizontal = 0;
    setHorizonIcon(horizontal);
  }
  sendDATA();
}

/*
   PAGE ZONE
*/
void next_page(void *ptr) {
  light.show();
  setLightIcon(light_mode);
  page_flag = 1;
}

void back_page(void *ptr) {
  aircon.show();
  NxTemp.setValue(temperature);
  setPwrBtnIcon(power_state);
  setModeIcon(opmode);
  setFanIcon(fan);
  setVertIcon(vertical);
  setHorizonIcon(horizontal);
  page_flag = 0;
}

/* LIGHT ZONE  */
void setLightIcon(uint32_t light_mode) {
  if (light_mode == 0) {
    NxLightPower.Set_background_image_pic(55);
    NxLSttOn.setPic(60);
    NxLSttDim.setPic(59);
    NxLSttNight.setPic(58);
    NxLSttOff.setPic(62);
  } else if (light_mode == 1) {
    NxLightPower.Set_background_image_pic(54);
    NxLSttDim.setPic(59);
    NxLSttNight.setPic(58);
    NxLSttOff.setPic(61);
    NxLSttOn.setPic(64);
  } else if (light_mode == 2) {
    NxLightPower.Set_background_image_pic(54);
    NxLSttOn.setPic(60);
    NxLSttNight.setPic(58);
    NxLSttOff.setPic(61);
    NxLSttDim.setPic(63);
  } else if (light_mode == 3) {
    NxLightPower.Set_background_image_pic(54);
    NxLSttOn.setPic(60);
    NxLSttDim.setPic(59);
    NxLSttOff.setPic(61);
    NxLSttNight.setPic(57);
  }
}

void LightPower(void *ptr) {
  if (light_pwr == 0) {
    light_mode = 1;
    light_pwr = true;
  } else if (light_pwr == 1) {
    light_mode = 0;
    light_pwr = false;
  }
  setLightIcon(light_mode);
  sendDATA();
}

void LightOn(void *ptr) {
  light_mode = 1;
  light_pwr = true;
  setLightIcon(light_mode);
  sendDATA();
}

void LightOff(void *ptr) {
  light_mode = 0;
  light_pwr = true;
  setLightIcon(light_mode);
  sendDATA();
}

void DimLight(void *ptr) {
  light_mode = 2;
  light_pwr = true;
  setLightIcon(light_mode);
  sendDATA();
}

void NightLight(void *ptr) {
  light_mode = 3;
  light_pwr = false;
  setLightIcon(light_mode);
  sendDATA();
}

void setup() {
  //Serial.begin(115200);
  if (!LittleFS.begin()) {
    return;
  }
  loadConfig();

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

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

  NxLightPower.attachPop(LightPower, &NxLightPower);
  NxLightOn.attachPop(LightOn, &NxLightOn);
  NxLightDim.attachPop(DimLight, &NxLightDim);
  NxLightNight.attachPop(NightLight, &NxLightNight);
  NxLightOff.attachPop(LightOff, &NxLightOff);

  if (page_flag == 0) {
    aircon.show();
    NxTemp.setValue(temperature);
    setPwrBtnIcon(power_state);
    setModeIcon(opmode);
    setFanIcon(fan);
    setVertIcon(vertical);
    setHorizonIcon(horizontal);
  } else if (page_flag == 1) {
    light.show();
    setLightIcon(light_mode);
  }
}

void loop() {
  nexLoop(nex_listen_list);
  if (millis() > 3600000) {
    saveConfig();
    ESP.restart();
  }
}
