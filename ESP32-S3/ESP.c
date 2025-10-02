#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "42-Student";
const char* password = "42ADisAwesome";

// Telegram BOT Token (from BotFather)
#define BOTtoken "8245407015:AAF5wSP0_SM4Vr4dMEo-3IRwvl7Za1qSMD0"

// Your Telegram User ID (get from @userinfobot)
#define CHAT_ID "6826032936"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
	Serial.begin(115200);

	// Connect to WiFi
	WiFi.begin(ssid, password);
	Serial.print("Connecting to WiFi");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("\nConnected to WiFi");
	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());

	// For HTTPS
	client.setInsecure();

	// Send a message
	bot.sendMessage(CHAT_ID, "Hello from ESP32! 🚀", "");
}

void loop() {
	// You can also check for new messages
	int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
	while(numNewMessages)
	{
		for (int i = 0; i < numNewMessages; i++)
		{
			String text = bot.messages[i].text;
			String chat_id = String(bot.messages[i].chat_id);

			if (text == "/status")
			{
				bot.sendMessage(chat_id, "ESP32 is running fine ✅", "");
			}
		}
		numNewMessages = bot.getUpdates(bot.last_message_received + 1);
	}
}
