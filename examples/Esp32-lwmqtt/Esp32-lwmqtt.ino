/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#include "esp32-mqtt.h"

void setup() {
  // код размещенный здесь будет выполнен единожды при запуске:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  setupCloudIoT();
}

unsigned long lastMillis = 0;
void loop() {
  mqttClient->loop();
  delay(10);  // <- исправляет некоторые проблемы со стабильностью WiFi соединения

  if (!mqttClient->connected()) {
    connect();
  }

  // публикует сообщение примерно каждую секунду.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    publishTelemetry(getDefaultSensor());
  }
}
