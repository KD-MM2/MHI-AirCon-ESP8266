#include <ESP8266WiFi.h>
#include <espnow.h>

#define RELAY_1 5
#define RELAY_2 4
#define RELAY_3 14

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int a;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.print("Bytes received: ");
  //Serial.println(len);
  if(myData.a == 0) {
    light_off();
  } else if(myData.a == 1) {
    light_on();
  } else if(myData.a == 2) {
    dim_light();
  } else if(myData.a == 3) {
    night_light();
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
