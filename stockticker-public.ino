// Including necessary libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Stepper.h>

// Declare OLED parameters
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool isInverted = false;

// Declare stepper motor parameters
// The pinout order is kind of weird
// I discovered a wiring mistake so this is to compensate
#define IN1 19
#define IN2 17
#define IN3 18
#define IN4 5
const int stepsPerRev = 2048;
Stepper motor(stepsPerRev, IN1, IN3, IN2, IN4);
int currentPos = 0;
const int motorSpeed = 5;

// Controls how sensitive the motor is to stock changes.
// I recommend a value between 100 and 200.
// Pointer points vertically when % change equals 512/response.
// Ex: when response = 100, pointer becomes vertical at 512/100 = 5.12%.
const int motorResponse = 150;

// Declare LED parameters
const int pinRed = 4;
const int pinGreen = 16;

// Choose network information
const char* ssid ="yourNetworkName";
const char* pass = "yourNetworkPassword";
bool isOffline = false;

// Choose stock information
const String key = "yourAPIKey";
const String symbol = "yourSymbol";

// How often the ticker refreshes
// 10000 ms is good for demomode 
// but for practical purposes every few minutes is probably better
const int updateTime = 10000;

void setup(){
  Serial.begin(115200);
  setupLED();
  setupDisplay();
  setupMotor();
  setupWiFi();
}

void loop(){
  float differenceInPrice = 0.0;
  if (isOffline == true){
    differenceInPrice = demoMode();
  }
  else{
    differenceInPrice = checkPrice();
  }
  changeLED(differenceInPrice);
  currentPos = driveMotor(differenceInPrice);
  delay(updateTime);
}

// LED setup
void setupLED(){
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinRed, LOW);
}

// Changes LED colour
void changeLED(float diff){
  if(diff >= 0){
    digitalWrite(pinGreen, HIGH);
    digitalWrite(pinRed, LOW);
  }
  else{
    digitalWrite(pinRed, HIGH);
    digitalWrite(pinGreen, LOW);
  }
}

// Display setuo
void setupDisplay(){
  delay(250);
  display.setTextColor(SH110X_WHITE);
  display.begin(i2c_Address, true);
  display.setContrast(0); 
  display.display();
  delay(2000);
  display.clearDisplay();
}

// Displays text on LCD
void displayText(int col, int row, String text, int size){
  display.setTextSize(size);
  display.setCursor(col, row);
  display.println(text);
  display.display();
}

// Displays stock information
void displayPrice(float current, float previous, float change){
  display.clearDisplay();
  String currentText = "$" + String(current);
  String previousText = "Prev: $" + String(previous);
  String changeText = "Change: " + String(change) + "%";
  printCenter(symbol, 0, 4, 1);
  printCenter(currentText, 0, 22, 2);
  printCenter(previousText, 0, 45, 1);
  printCenter(changeText, 0, 54, 1);
}

// Inverts the display
void invertDisplay(){
  if (isInverted == false){
    display.invertDisplay(true);
    isInverted = true;
    return;
  }
  display.invertDisplay(false);
  isInverted = false;
  return;
}

// Center text on the OLED
void printCenter(const String buf, int x, int y, int size){
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(size);
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h);                     
  display.setCursor((x - w / 2) + (128 / 2), y);                          
  display.print(buf);
  display.display();                                                     
}

// Fetches stock info
// and returns differenceInPrice for the motor and LED
float checkPrice(){
  HTTPClient http;
  int httpCode;
  http.begin("https://finnhub.io/api/v1/quote?symbol=" + symbol + "&token=" + key);
  httpCode = http.GET();

  float differenceInPrice = 0;

  if(httpCode > 0){
    DynamicJsonDocument doc(1024);
    String payload = http.getString();
    // Serial.println(payload);
    deserializeJson(doc, payload);

    float previousClosePrice = doc["pc"];
    float currentPrice = doc["c"];
    if (currentPrice == 0){
      display.clearDisplay();
      displayText(0, 0, "No Available Info!", 1);
      displayText(0, 8, "Entering Demo Mode.", 1);
      isOffline = true;
      delay(3000);
      http.end();
      return 0;
    }
    differenceInPrice = ((currentPrice-previousClosePrice)/previousClosePrice)*100.0;
    displayPrice(currentPrice, previousClosePrice, differenceInPrice);
  } 
  else{
    display.clearDisplay();
    displayText(0, 0, "HTTP Req. Error!", 1);
    displayText(0, 8, "Entering Demo Mode.", 1);
    isOffline = true;
  }
  http.end();
  return differenceInPrice;
}

// Set up WiFi
void setupWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  displayText(0, 0, "Connecting to WiFi", 1);
  delay(1000);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED){
    displayText(2*i, 10, ".", 1);
    i++;
    delay(1000);
    if (i == 10){
      isOffline = true;
      break;
    }
  } 
  display.clearDisplay();
  if (isOffline == false){
    displayText(0, 0, "Connection Success!", 1);
  }
  else{
    displayText(0, 0, "Connection Failed!", 1);
    displayText(0, 8, "Entering Demo Mode.", 1);
  }
  delay(3000);
}

// Setup motor
void setupMotor(){
  motor.setSpeed(motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Sets the motor output pins to high low
// Function used to conserve power
// 1 -> on, 0 -> off
void motorPower(bool onoff){
  if (onoff == true){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    return;
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  return;
}

// Positions the motor based on % change
// Returns # of steps to track relative position
int driveMotor(float diff){
  motorPower(true);
  invertDisplay();
  int targetPos = round(diff*motorResponse);
  if (diff > 512/motorResponse)
  {
    targetPos = 512;
  } 
  else if (diff < -512/motorResponse)
  {
    targetPos = -512;
  }
  motor.step(targetPos - currentPos);
  motorPower(false);
  invertDisplay();
  return targetPos;
}

// Generating information if API is unreachable
float demoMode(){
  float randomDiff = random(-256, 256);
  randomDiff = randomDiff/100.0;
  displayPrice(randomDiff + 100.00, 100.00, randomDiff);
  return randomDiff;
}
