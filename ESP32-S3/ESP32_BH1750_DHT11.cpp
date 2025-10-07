#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "42-Student";
const char* password = "42ADisAwesome";

// Telegram BOT Token (from BotFather)
#define BOTtoken "8245407015:AAF5wSP0_SM4Vr4dMEo-3IRwvl7Za1qSMD0"

// Your Telegram User ID (get from @userinfobot)h
#define CHAT_ID "6826032936"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// For the BH1750
#include <Wire.h>
#include <BH1750.h>
int	l = 0;
BH1750 lightMeter;
float lux;

// DHT-11 Sensor
#include "DHT.h"
#define DHTPIN 11       // Pin connected to the DHT11 data line
#define DHTTYPE DHT11  // DHT11 sensor type
float humidity;
float temperature; // Celsius

DHT dht(DHTPIN, DHTTYPE);

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
	{
		Serial.println("BH1750 sensor initialized.");
		float lux = lightMeter.readLightLevel();
	}
	else
	{
		Serial.println("Error: BH1750 not detected.");
		l = 1;
	}
	
	//DHT-11
	Serial.begin(115200);
	dht.begin();
	Serial.println("DHT11 test starting...");
	float humidity = dht.readHumidity();
	float temperature = dht.readTemperature(); // Celsius
}

void loop() {
	// You can also check for new messages
	int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
	
	// buffer for your message
	char message[100];

	while(numNewMessages)
	{
		for (int i = 0; i < numNewMessages; i++)
		{
			String text = bot.messages[i].text;
			String chat_id = String(bot.messages[i].chat_id);
		
			Serial.println("message recieved");

			if (text == "/status")
			{
				bot.sendMessage(chat_id, "ESP32 is running fine ✅", "");
			}
			else if (text == "/light")
			{
				if (l == 0)
				{
					lux = lightMeter.readLightLevel();
					Serial.print("Light: ");
					Serial.print(lux);
					Serial.println(" lx");
					sprintf(message, "Light: %.2f lx", lux);
					bot.sendMessage(chat_id, message, "");
				}
				else if (l == 1)
				{
					bot.sendMessage(chat_id, "Not connected/working", "");
				}
			}
			else if (text == "/humid")
			{
				humidity = dht.readHumidity();
				if (isnan(humidity))
				{
					Serial.println("Failed to read from DHT sensor!");
					bot.sendMessage(chat_id, "Failed to read from DHT sensor!", "");
				}
				else
				{
					sprintf(message, "Humidity: %.2f %", humidity);
					Serial.print("Humidity: ");
					Serial.print(humidity);
					Serial.print(" %\t");
				}
			}
			else if (text == "/temp")
			{
				// float tempF = dht.readTemperature(true);   // Fahrenheit
				temperature = dht.readTemperature(); // Celsius
				if (isnan(temperature))
				{
					Serial.println("Failed to read from DHT sensor!");
					bot.sendMessage(chat_id, "Failed to read from DHT sensor!", "");
				}
				else
				{
					Serial.print("Temperature: ");
					Serial.print(temperature);
					Serial.println(" °C");
					sprintf(message, "Temperature: %.2f °C", temperature);
				}
			}
			else
				bot.sendMessage(chat_id, "Command not recognised", "");

		}
		numNewMessages = bot.getUpdates(bot.last_message_received + 1);
	}
}
