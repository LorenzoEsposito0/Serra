#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11   
#define pResistor A5
#define sms A0
#define waterSensor A1

int strisciaLed = 12;
int Innaffiatore = 7;
int motoreVentola = 4;
int buzzer = 9;

const int sogliaMinimaLuce = 10;
const int sogliaMinimaAcqua = 60;
const int sogliaMinimaUmidita = 40;
const int sogliaMinimaTemperatura = 20;

LiquidCrystal_I2C lcd(0x27,  16, 2); //dimensioni schermo, coordinate  massime
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    
    pinMode(strisciaLed, OUTPUT);
    pinMode(motoreVentola, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(Innaffiatore, OUTPUT);
        
    Serial.begin(9600);
    lcd.init(); //Inizializza il display LCD
    lcd.backlight(); //Accende la retroilluminazione del display
    dht.begin();
}

void loop() {
    
   //Lettura luce
    int lightRead = analogRead(pResistor);
    int light = map(lightRead, 0, 700, 0, 100);
    
   //Lettura temperatura aria
    int temperaturaAria = dht.readTemperature();//temperatura in gradi
    
   //Lettura umidita terreno
    float umiTerrenoRead = analogRead(sms); 
    int umiditaTerreno = map(umiTerrenoRead, 0, 1023, 100, 0);
   
   //Lettura livello acqua
    int livAcqua = analogRead(waterSensor);
    int livelloAcqua = livAcqua/3.8;
    
  //LUCE
    if(light<sogliaMinimaLuce){
        digitalWrite(strisciaLed, HIGH); 
    } 
    else
    {
        digitalWrite(strisciaLed, LOW); 
    }

  //LIVELLO ACQUA
    if(livelloAcqua<sogliaMinimaAcqua)
    {
      digitalWrite(buzzer, HIGH);
    }
    else
    {
      digitalWrite(buzzer, LOW);  
    }

  //TEMPERATURA ARIA
    if(temperaturaAria>sogliaMinimaTemperatura){
        digitalWrite(motoreVentola, HIGH);
    } 
    else
    {
        digitalWrite(motoreVentola, LOW);
    }
  
  //UMIDITA' TERRENO
    if(umiditaTerreno<sogliaMinimaUmidita){
       if(livelloAcqua>sogliaMinimaAcqua){
          digitalWrite(Innaffiatore, HIGH); 
       }
       else
       {
        digitalWrite(Innaffiatore, LOW); 
       }
    } 
    else
    {
        digitalWrite(Innaffiatore, LOW); 
    }
    
  
//Scrittura sul monitor seriale
    Serial.println("----------------------------");
    Serial.println("Temperatura aria: " + String(temperaturaAria) + "°C");
    Serial.println("Umidità terreno: " + String(umiditaTerreno) + "%");
    Serial.println("Livello acqua: " + String(livelloAcqua) + "%");
    Serial.println("Luce: " + String(light) + "%");

//Scrittura sullo schermo lcd
    lcd.setCursor(0, 0); 
  
  //Temperatura aria - TA
    lcd.print("TA:" + String(temperaturaAria));
    lcd.write(223);
    lcd.print("C -");

  //Umidità terreno - UT
    lcd.print("UT:" + String(umiditaTerreno) + "%");
    
    lcd.setCursor(0, 1); 
  
  //Livello acqua - WL
    lcd.print("WL:" + String(livelloAcqua) + "% -");  
  
  //Luce ambientale - LA
    lcd.print("LA:" + String(light) + "%"); 
  
  delay(200);
  lcd.clear();
}
