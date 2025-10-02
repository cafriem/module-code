#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Merlyn";
const char* password = "afriemmm23";

// Telegram BOT Token (from BotFather)
#define BOTtoken "8245407015:AAF5wSP0_SM4Vr4dMEo-3IRwvl7Za1qSMD0"

// Your Telegram User ID (get from @userinfobot)
#define CHAT_ID "6826032936"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// For the BH1750
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

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


	Serial.begin(115200);

	// Initialize I2C (you can change pins if needed)
	Wire.begin(12, 13);  // SDA, SCL

	if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
		Serial.println("BH1750 sensor initialized.");
	else
		Serial.println("Error: BH1750 not detected.");
	
	
	}
	
	void loop() {
	// You can also check for new messages
	int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
	
	char message[100];   // buffer for your message

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
			else if (text == "/light")
			{
				float lux = lightMeter.readLightLevel();
				Serial.print("Light: ");
				Serial.print(lux);
				Serial.println(" lx");
				sprintf(message, "Light: %.2f lx", lux);
				bot.sendMessage(chat_id, message, "");
			}
		}
		numNewMessages = bot.getUpdates(bot.last_message_received + 1);
	}
}
