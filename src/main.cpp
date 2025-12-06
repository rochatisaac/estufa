//IMPORTS
#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

//PINS
const int DHT11_PIN = 2;
const int HOT_LED_PIN = 7;
const int COLD_LED_PIN = 4;

//CONSTANTS
DHT dht(DHT11_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int MAX_TEMP = 30;
const int MIN_TEMP = 15;

//VARIABLES
float temperature;
float airHumidity;

void setup()
{
  pinMode(HOT_LED_PIN, OUTPUT);
  pinMode(COLD_LED_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.init();
}

void loop()
{
  delay(1000);

  temperature = dht.readTemperature();
  airHumidity = dht.readHumidity();

  if (temperature > MAX_TEMP)
  {
    digitalWrite(HOT_LED_PIN, HIGH);
  } else 
  {
    digitalWrite(HOT_LED_PIN, LOW);
    if(temperature < MIN_TEMP)
    {
      digitalWrite(COLD_LED_PIN, HIGH);
    } else
    {
     digitalWrite(COLD_LED_PIN, LOW); 
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temperature) + (char) 223 + "C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: " + String(airHumidity) + "%");
}
