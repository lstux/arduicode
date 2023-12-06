#include <Arduino.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASS "your_wifi_pass"
#define NTP_POOL_SERVER "pool.ntp.org"
#define LOOP_DELAY 10000

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <RTClib.h>

WiFiUDP ntpUDP;
NTPClient *ntpcli=NULL;
RTC_DS3231 *rtc=NULL;

void setup() {
  Serial.begin(115200);
  rtc = new RTC_DS3231();
  if (!rtc->begin()) {
    Serial.println("DS3231 initialization failed");
    while (true) {}
  }
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print("Can't connect to WiFi network ");
    Serial.println(WIFI_SSID);
    while (true) {}
  }
  ntpcli = new NTPClient(ntpUDP);
  ntpcli->begin();
  if (!strcmp(NTP_POOL_SERVER, "")) ntpcli->setPoolServerName(NTP_POOL_SERVER);
}

void loop() {
  Serial.println("Getting NTP time");
  ntpcli->update();
  if (!ntpcli->isTimeSet()) {
    Serial.println("Can't get NTP time");
  else {
    Serial.println("NTP time retrieved, setting RTC time");
    rtc->adjust(DateTime(ntpcli->getEpochTime()));
  }
  delay(LOOP_DELAY);
}
