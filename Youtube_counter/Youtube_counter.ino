// Powered By Arduino classroom Youtube Channel

#include <WiFi.h>

#include <WiFiClientSecure.h>

#include <YoutubeApi.h>

#include <ArduinoJson.h>

const char ssid[] = "Your WIFI Router SSID";
const char password[] = "Your WIFI Router Password";

#define API_KEY "Enter Your API key"
#define CHANNEL_ID "Enter Your Channel ID"

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long timeBetweenRequests = 60 * 1000;  // 60 seconds, in milliseconds

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("\nConnecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();
}

void loop() {
  if (api.getChannelStatistics(CHANNEL_ID)) {
    Serial.println("\n---------Stats---------");

    Serial.print("Subscriber Count: ");
    Serial.println(api.channelStats.subscriberCount);

    Serial.print("View Count: ");
    Serial.println(api.channelStats.viewCount);

    Serial.print("Video Count: ");
    Serial.println(api.channelStats.videoCount);

    Serial.println("------------------------");
  }
  delay(timeBetweenRequests);
}
