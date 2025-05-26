#include "DHT.h"  // Librería DHT

#define DHTPIN 28      // Pin del sensor DHT21 AM2301
#define DHTTYPE DHT21  // Modelo del sensor DHT

DHT dht(DHTPIN, DHTTYPE);

// Pines de salida con nombres descriptivos
const int abanicoIzquierdoPin = 2;
const int abanicoDerechoPin = 3;
const int bombaDeAguaPin = 4;
const int ledRojoPin = 5;
const int ledAzulPin = 6;

// Pin de entrada para sensor de humedad del suelo
const int sensorHumedadSueloPin = A15;

void setup() {
  Serial.begin(9600);
  Serial.println("Test DHT21 AM2301");
  dht.begin();

  // Configuración de pines
  pinMode(sensorHumedadSueloPin, INPUT);

  pinMode(abanicoIzquierdoPin, OUTPUT);
  pinMode(abanicoDerechoPin, OUTPUT);
  pinMode(bombaDeAguaPin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);
  pinMode(ledAzulPin, OUTPUT);

  // Asegurarse de que todo esté apagado al inicio
  digitalWrite(abanicoIzquierdoPin, LOW);
  digitalWrite(abanicoDerechoPin, LOW);
  digitalWrite(bombaDeAguaPin, LOW);
  digitalWrite(ledRojoPin, LOW);
  digitalWrite(ledAzulPin, LOW);
}

void loop() {
  PruebasDeEncendido();

  /*
  delay(3000);
  SensorDeHumedad();
  SensorDeTemperaturaYHumedad();
  EncenderLuces();
  delay(3000);
  */
}

void SensorDeHumedad() {
  int humedad = analogRead(sensorHumedadSueloPin);
  Serial.print("Humedad del suelo: ");
  Serial.println(humedad);

  if (humedad < 500) {
    Serial.println("Humedad baja - Activando bomba de agua...");
    EncenderBombaDeAgua();
  } else {
    Serial.println("Humedad adecuada.");
  }
}

// Funcion de BombaDeAgua
void EncenderBombaDeAgua() {
  digitalWrite(bombaDeAguaPin, HIGH);
}

void ApagarBombaDeAgua(){
  digitalWrite(bombaDeAguaPin, LOW);
}

void SensorDeTemperaturaYHumedad() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Humedad: ");
  if (isnan(h)) {
    Serial.println("Error al leer la humedad");
  } else {
    Serial.print(h);
    Serial.println(" %");
  }

  Serial.print("Temperatura: ");
  if (isnan(t)) {
    Serial.println("Error al leer la temperatura");
  } else {
    Serial.print(t);
    Serial.println(" °C");
  }
}

//Funciones de Ventiladores
void EncenderVentiladores() {
  digitalWrite(abanicoIzquierdoPin, HIGH);
  digitalWrite(abanicoDerechoPin, HIGH);
}

void ApagarVentiladores(){
  digitalWrite(abanicoIzquierdoPin, LOW);
  digitalWrite(abanicoDerechoPin, LOW);
}

//Funciones de Luces
void EncenderLuces() {
  digitalWrite(ledRojoPin, HIGH);
  digitalWrite(ledAzulPin, HIGH);
}

void ApagarLuces(){
  digitalWrite(ledRojoPin, LOW);
  digitalWrite(ledAzulPin, LOW);
}

void PruebasDeEncendido() {
  digitalWrite(ledRojoPin, HIGH);
  delay(3000);
  digitalWrite(ledRojoPin, LOW);
  delay(3000);

  digitalWrite(ledAzulPin, HIGH);
  delay(3000);
  digitalWrite(ledAzulPin, LOW);
  delay(3000);

  digitalWrite(abanicoIzquierdoPin, HIGH);
  delay(3000);
  digitalWrite(abanicoIzquierdoPin, LOW);
  delay(3000);

  digitalWrite(abanicoDerechoPin, HIGH);
  delay(3000);
  digitalWrite(abanicoDerechoPin, LOW);
  delay(3000);

  digitalWrite(bombaDeAguaPin, HIGH);
  delay(3000);
  digitalWrite(bombaDeAguaPin, LOW);
  delay(3000);
}
