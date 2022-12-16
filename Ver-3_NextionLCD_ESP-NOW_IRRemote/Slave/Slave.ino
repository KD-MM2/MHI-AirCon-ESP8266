#include <ESP8266WiFi.h>
#include <espnow.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_MitsubishiHeavy.h>

#define RELAY_1 4
#define RELAY_2 5
#define RELAY_3 12

const uint16_t kIrLed = 14;

// Structure example to receive data
// Must match the sender structure
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

IRMitsubishiHeavy152Ac ac(kIrLed);

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  
  if (myData.id == 0) {
    ac.setPower(myData.power_state);
    ac.setFan(myData.fan);
    ac.setMode(myData.opmode);
    ac.setTemp(myData.temperature);
    ac.setSwingVertical(myData.vertical);
    ac.setSwingHorizontal(myData.horizontal);
    ac.send();
  } else if (myData.id == 1) {
    if (myData.light_mode == 0) {
      light_off();
    } else if (myData.light_mode == 1) {
      light_on();
    } else if (myData.light_mode == 2) {
      dim_light();
    } else if (myData.light_mode == 3) {
      night_light();
    }
  }
}

void light_on() {
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
}
void light_off() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
}
void dim_light() {
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, LOW);
}
void night_light() {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, HIGH);
}

void setup() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);

  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);

  ac.begin();

  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
