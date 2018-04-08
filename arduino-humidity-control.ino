#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN_Lavanderia   48
#define DHTPIN_Bagno        49
#define DHTPIN_Lavandino    40
#define DHTPIN_Aerazione    41
#define DHTPIN_Stufa        32

#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

#define PIN_Bottone         26

int contatore = 0;

String nomi_sensori[] = {"Lavanderia", "Bagno", "Lavandino", "Aerazione", "Stufa"};
DHT_Unified dhts[5] = {DHT_Unified(DHTPIN_Lavanderia,DHTTYPE), DHT_Unified(DHTPIN_Bagno,DHTTYPE), DHT_Unified(DHTPIN_Lavandino,DHTTYPE), DHT_Unified(DHTPIN_Aerazione,DHTTYPE), DHT_Unified(DHTPIN_Stufa,DHTTYPE)};

sensors_event_t events[5] = {sensors_event_t(), sensors_event_t(), sensors_event_t(), sensors_event_t(), sensors_event_t()};
uint32_t delayMS;

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600); 
  for(int i = 0; i < 5; i++){
    dhts[i].begin();
  }

  pinMode(53,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(37,OUTPUT);
  pinMode(35,OUTPUT);

  pinMode(PIN_Bottone, INPUT);
  
  pinMode(49,INPUT);
  pinMode(48,INPUT);
  pinMode(41,INPUT);
  pinMode(40,INPUT);
  pinMode(33,INPUT);

  digitalWrite(53,1);
  digitalWrite(51,0);
  digitalWrite(52,1);
  digitalWrite(50,0);
  digitalWrite(44,1);
  digitalWrite(42,0);
  digitalWrite(45,1);
  digitalWrite(43,0);
  digitalWrite(37,1);
  digitalWrite(35,0);
  
  Serial.println("Inizializzazione...");
}

void loop() {

  int buttonState = digitalRead(PIN_Bottone);

  if(buttonState == HIGH){
    contatore = (contatore + 1) % 4;
    
    delay(delayMS);
    
    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.print("");
    for(int a = 0; a < centerString(nomi_sensori[contatore]); a++){
      lcd.print(" ");
    }
    lcd.print(nomi_sensori[contatore]);
    
    lcd.setCursor(0,1);

    sensors_event_t event;
    
    dhts[contatore].temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println("Error reading temperature!");
    } else {
      lcd.print(" T:");
      lcd.print((int)event.temperature);
      lcd.print(" C ");
    }

    dhts[contatore].humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println("Error reading humidity!");
    } else {
      lcd.print(" U:");
      lcd.print((int)event.relative_humidity);
      lcd.print(" %");
    }
  }

  delay(1000);
}

int centerString(String nome){
  int wordL = nome.length(),  L = 16;
  return (L - wordL) / 2;
}
