#include "DHT.h"  // Librería DHT

#define DHTPIN1 11     // Primer sensor DHT21
#define DHTPIN2 12     // Segundo sensor DHT21
#define DHTTYPE DHT21  // Modelo del sensor DHT

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// Pines de salida con nombres descriptivos
const int abanicoIzquierdoPin = 2;
const int abanicoDerechoPin = 3;
const int bombaDeAguaPin = 4;
const int ledRojoPin = 5;
const int ledAzulPin = 6;
const int releSensor1 = 7;
const int releSensor2 = 8;
const int releSensor3 = 9;
const int releSensor4 = 10;

// Pines de entrada para sensores de humedad del suelo
const int sensorHumedadSuelo1Pin = A0;
const int sensorHumedadSuelo2Pin = A1;

void setup() {
  Serial.begin(9600);
  Serial.println("Test DHT21 AM2301 x2");
  dht1.begin();
  dht2.begin();

  // Configuración de pines
  pinMode(sensorHumedadSuelo1Pin, INPUT);
  pinMode(sensorHumedadSuelo2Pin, INPUT);

  pinMode(abanicoIzquierdoPin, OUTPUT);
  pinMode(abanicoDerechoPin, OUTPUT);
  pinMode(bombaDeAguaPin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);
  pinMode(ledAzulPin, OUTPUT);

  pinMode(releSensor1, OUTPUT);
  pinMode(releSensor2, OUTPUT);
  pinMode(releSensor3, OUTPUT);
  pinMode(releSensor4, OUTPUT);

  // Asegurarse de que todo esté apagado al inicio
  digitalWrite(abanicoIzquierdoPin, LOW);
  digitalWrite(abanicoDerechoPin, LOW);
  digitalWrite(bombaDeAguaPin, LOW);
  digitalWrite(ledRojoPin, LOW);
  digitalWrite(ledAzulPin, LOW);

  digitalWrite(releSensor1, LOW);
  digitalWrite(releSensor2, LOW);
  digitalWrite(releSensor3, LOW);
  digitalWrite(releSensor4, LOW);
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
  int humedad1 = analogRead(sensorHumedadSuelo1Pin);
  int humedad2 = analogRead(sensorHumedadSuelo2Pin);

  Serial.print("Humedad del suelo 1: ");
  Serial.println(humedad1);
  Serial.print("Humedad del suelo 2: ");
  Serial.println(humedad2);

  if (humedad1 < 500 || humedad2 < 500) {
    Serial.println("Humedad baja - Activando bomba de agua...");
    EncenderBombaDeAgua();
  } else {
    Serial.println("Humedad adecuada.");
    ApagarBombaDeAgua();
  }
}

// Función de BombaDeAgua
void EncenderBombaDeAgua() {
  digitalWrite(bombaDeAguaPin, HIGH);
}

void ApagarBombaDeAgua(){
  digitalWrite(bombaDeAguaPin, LOW);
}

void SensorDeTemperaturaYHumedad() {
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  Serial.println("Sensor DHT1:");
  Serial.print("Humedad: ");
  Serial.print(h1);
  Serial.println(" %");
  Serial.print("Temperatura: ");
  Serial.print(t1);
  Serial.println(" °C");

  Serial.println("Sensor DHT2:");
  Serial.print("Humedad: ");
  Serial.print(h2);
  Serial.println(" %");
  Serial.print("Temperatura: ");
  Serial.print(t2);
  Serial.println(" °C");
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

  digitalWrite(releSensor1, HIGH);
  delay(3000);
  digitalWrite(releSensor1, LOW);
  delay(3000);

  digitalWrite(releSensor2, HIGH);
  delay(3000);
  digitalWrite(releSensor2, LOW);
  delay(3000);

  digitalWrite(releSensor3, HIGH);
  delay(3000);
  digitalWrite(releSensor3, LOW);
  delay(3000);

  digitalWrite(releSensor4, HIGH);
  delay(3000);
  digitalWrite(releSensor4, LOW);
  delay(3000);
}
