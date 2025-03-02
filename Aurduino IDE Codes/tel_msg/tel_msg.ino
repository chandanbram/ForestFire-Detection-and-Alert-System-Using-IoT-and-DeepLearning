#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "username";
const char* password = "password";

// Initialize Telegram BOT
#define BOTtoken "bottoken"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "chatid"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
 
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Eco-Harbor Connected successfully", "");
}

void loop() {
  if(digitalRead(D5) == 1) { // PIR Motion Sensor
    bot.sendMessage(CHAT_ID, "Alert! \n   Forest Fire detected! \n   Camera No: 01 \n\n   Immediate action needed! \n\n ---------------------------------------------- \n \n अलर्ट!\n   जंगली आग का पता लगा!\n   कैमरा नंबर: 01 \n\n   तत्काल कार्रवाई की आवश्यकता है! \n\n ---------------------------------------------- \n \n ಎಚ್ಚರಿಕೆ!\n   ಕಾಡ್ಗಿಚ್ಚು ಗುರುತಿಸಲಾಗಿದೆ!\n   ಕ್ಯಾಮರಾ ಸಂಖ್ಯೆ: 01 \n \n   ತಕ್ಷಣ ಕ್ರಮದ ಅಗತ್ಯವಿದೆ!",  "");
    Serial.println("Fire detected!");
    delay(1000); // delay to avoid continuous messaging
  }
}
