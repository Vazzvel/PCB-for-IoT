/*
 *Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: M. en I. Valente Vázquez Velázquez
 *Última modificación: 1-agosto-2025
 *https://sites.google.com/ciencias.unam.mx/introduccion-iot-fc/inicio
 *
*/

//Incluir biblioteca del sensor DHT
#include "DHT.h"

//Definir pines a utilizar
#define DHTTYPE DHT11
#define DHTPIN 32
#define PinBotton_PullUp 4
#define PinBotton_PullDown 15
#define PinPOT 35
#define PinLDR 34

//Declarar variables globales
int leds[5] = {14, 27, 26, 25, 33};
long tiempo = 0;
bool state = HIGH;

//Llamar a objeto del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  //Inicializar la comunicación serial
  Serial.begin(115200);

  //Inicializar pines de entrada y salida
  pinMode(PinBotton_PullUp, INPUT);
  pinMode(PinBotton_PullDown, INPUT);
  pinMode(PinPOT, INPUT);
  pinMode(PinLDR, INPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  //Inicializar sensor DHT
  Serial.println(F("DHTxx test!"));
  dht.begin();
  tiempo = millis();
}

void loop() {
  //Leer e imprimir los valores de los sensores
  //y encender y apagar los leds cada 2 segundos
  while(millis()-tiempo < 2000){  
    for (int i = 0; i < 5; i++) {
      digitalWrite(leds[i], state);
    }  
    Serial.print(digitalRead(PinBotton_PullUp));
    Serial.print(", ");
    Serial.print(digitalRead(PinBotton_PullDown));
    Serial.print(", ");
    Serial.print(analogRead(PinPOT));
    Serial.print(", ");
    Serial.println(analogRead(PinLDR));
    delay(200); 
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else{
    Serial.print("H: ");
    Serial.print(h);
    Serial.print("%  T: ");
    Serial.print(t);
    Serial.println("°C ");
  }
  
  state = !state;
  tiempo = millis();
  delay(200);
}
