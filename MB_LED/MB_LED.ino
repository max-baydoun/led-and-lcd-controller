#include <Arduino.h>
#include <LiquidCrystalIO.h>

// When using the I2C version, these two extra includes are always needed. Doing this reduces the memory slightly for
// users that are not using I2C.
#include <IoAbstractionWire.h>
#include <Wire.h>

constexpr uint8_t LED_PIN = 5;
constexpr uint8_t GND_PIN = 2;
constexpr uint16_t FUNCTION_ARRAY_SIZE = 7;
constexpr uint16_t PARAMETER_ARRAY_SIZE = 20;
constexpr uint16_t NET_ARRAY_SIZE = FUNCTION_ARRAY_SIZE + PARAMETER_ARRAY_SIZE + 1;
constexpr uint16_t WORD_COUNT = 5;
constexpr uint16_t MAX_CHAR_COUNT = 13;

LiquidCrystalI2C_RS_EN(lcd, 0x27, false)

char command[FUNCTION_ARRAY_SIZE + PARAMETER_ARRAY_SIZE + 1];
bool state = 0;


void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(GND_PIN, OUTPUT);
    digitalWrite(GND_PIN, LOW);
    Serial.begin(9600);
    Serial.setTimeout(10);
    Wire.begin();

     // Set up the LCD's number of columns and rows, must be called.
    lcd.begin(16, 2);

    // Most backpacks have the backlight on pin 3.
    lcd.configureBacklightPin(3);
    lcd.backlight();
    lcd.clear();
}

void loop() {
    while (Serial.available() > 0){
        Serial.readString().toCharArray(command, NET_ARRAY_SIZE + 1);
        command[NET_ARRAY_SIZE + 1] = '\0';
        lcd.clear();
        if(strstr(command, "blink")) {
          lcd.print("Blinking");
          long parameters[2];
          strtok(command, " ");
          parameters[0] = strtol(strtok(NULL, " "), NULL, 10);
          parameters[1] = strtol(strtok(NULL, " "), NULL, 10);
          blink_function(parameters[0], parameters[1]);
        }
        else if(strstr(command, "toggle")) {
          char* toggleSay = state ? "Toggle off" : "Toggle on";
          lcd.print(toggleSay);
          toggle_function();
          delay(500);
        }
        lcd.clear();

    }
}

void blink_function(long delay_time_in_ms, long duration) {
  Serial.print("BLINKING FOR ");
  Serial.print(duration);
  Serial.print(" ITERATIONS WITH A DELAY TIME OF ");
  Serial.print(delay_time_in_ms);
  Serial.println(" MILLISECONDS");
  int iteration = 0;
  while (iteration < duration){
      digitalWrite(LED_PIN, HIGH);
      delay(delay_time_in_ms);
      digitalWrite(LED_PIN, LOW);
      delay(delay_time_in_ms);
      iteration += 1;
  }
}

void toggle_function() {
  Serial.println("TOGGLING");
  uint8_t val = state ? LOW : HIGH;
  digitalWrite(LED_PIN, val);
  state = !state;
}
