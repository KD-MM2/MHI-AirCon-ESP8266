#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_MitsubishiHeavy.h>
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
int temperature, fan, opmode, vertical, horizontal;
bool power_state;

IRMitsubishiHeavy152Ac ac(kIrLed);

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

void setup() {
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
}

void loop() {
  nexLoop(nex_listen_list);
}
