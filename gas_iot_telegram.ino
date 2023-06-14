
// library yang dibutuhkan
// CTBot at version 2.1.9
// ArduinoJson at version 6.21.2
// LiquidCrystal I2C at version 1.1.2 

#include <CTBot.h>
#include <LiquidCrystal_I2C.h>
#include "mq2.h"


String nama_wifi = "LAC";                                         // REPLACE mySSID WITH YOUR WIFI SSID
String password_wifi = "Larissa78";                               // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "6027481324:AAFF4CvF0nweqnPNfa3lTuUe9S3VKFi6Ra4";  // Token Telegram bot
#define myId 1901323529                                           // Id Telegram penerima

int sensor_pin = A0;
const int buzer = D8;
const int ledRed = D7;
const int ledGreen = D6;

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
CTBot myBot;
mq2 Sensor = mq2(A0);

void setup() {
  pinMode(buzer, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  lcd.init();  // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Calibrasi Sensor");
  lcd.setCursor(0, 1);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting To");
  lcd.setCursor(0, 1);
  lcd.print(nama_wifi);

  myBot.wifiConnect(nama_wifi, password_wifi);  // connect the ESP8266 to the desired access point
  myBot.setTelegramToken(token);  // set the telegram bot token
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Berhasil Terhubung");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test Koneksi");
  lcd.setCursor(0, 1);
  lcd.print("ke Telegram bot");
  lcd.setCursor(0, 1);
  if (myBot.testConnection())  // check if all things are ok
  {
    lcd.print("Koneksi Sukses ");
  } else {
    lcd.print("Gagal Terkoneksi");
  }
  delay(1000);
}

void loop() {
  float lpg = Sensor.getPpm();  // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kadar LPG");
  lcd.setCursor(0, 1);
  lcd.print(lpg);
  lcd.print(" Ppm");

  if (lpg > 1000) {
    digitalWrite(buzer, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    TBMessage msg;
    msg.text = "Terjadi Kebocoran Gas, kadar LPG = " + String(lpg) + " Ppm";
    myBot.sendMessage(myId, msg.text);
  } else {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzer, LOW);
  }
  delay(1000);
}


