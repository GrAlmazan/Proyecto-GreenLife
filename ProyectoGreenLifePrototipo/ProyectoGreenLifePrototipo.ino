#include "DHT.h"  // Liberia DHT

#define DHTPIN 28      //Pin del sensor DHT21 AM23O1
#define DHTTYPE DHT21  //Defnimos el modelo del sensor DHT21 AM2301

DHT dht(DHTPIN, DHTTYPE);

//Variables de encendido (Salida)
const int encendidoSensorHumedadYTemperatura = 52;
const int encendidoSensorHumedad = 50;
const int encendidoBombaDeAgua = 48;
const int encendidoLucesUV = 42;
const int encendidoVentilador = 38;

//Variable de datos (Entrada)
const int sensorPin = A15;

void setup() {
  Serial.begin(9600);                   // Se inicia la comunicación serial
  Serial.println("Test DHT21 AM2301");  // Mensaje de inicialización
  dht.begin();                          // Inicializamos el sensor DHT

  // Configuración de pines
  pinMode(sensorPin, INPUT);                            // Entrada de datos del sensor
  pinMode(encendidoSensorHumedadYTemperatura, OUTPUT);  // Control del sensor de humedad y temperatura
  pinMode(encendidoSensorHumedad, OUTPUT);              // Control del sensor de humedad
  pinMode(encendidoBombaDeAgua, OUTPUT);                // Control de la bomba de agua
  pinMode(encendidoLucesUV, OUTPUT);                    // Control de las luces UV
  pinMode(encendidoVentilador, OUTPUT);                 // Control del ventilador

  // Asegurarse de que todos estén apagados al inicio
  digitalWrite(encendidoSensorHumedadYTemperatura, LOW);
  digitalWrite(encendidoSensorHumedad, LOW);
  digitalWrite(encendidoBombaDeAgua, LOW);
  digitalWrite(encendidoLucesUV, LOW);
  digitalWrite(encendidoVentilador, LOW);
}


void loop() {
  PruebasDeEncendido();


  // Funcionamiento basico
  /*
  delay(3000);
  SensorDeHumedad();
  SensorDeTemperaturaYHumedad();
  LucesUV();
  delay(3000);
  */
}

void SensorDeHumedad() {
  // Sensor de humedad en tierra
  digitalWrite(encendidoSensorHumedad, HIGH);
  int humedad = analogRead(sensorPin);  // Leer humedad del suelo
  Serial.print("Humedad del suelo: ");
  Serial.println(humedad);

  if (humedad < 500) {
    Serial.println("Humedad baja - Realizando acción...");
    BombaDeAgua();
    delay(1000);
  } else {
    Serial.println("Humedad adecuada.");
  }
  digitalWrite(encendidoSensorHumedad, LOW);
}

void BombaDeAgua() {
  //Encender Bomba por 3 segundos
  digitalWrite(encendidoBombaDeAgua, HIGH);
  delay(3000);
  digitalWrite(encendidoBombaDeAgua, LOW);
  delay(3000);
}

void SensorDeTemperaturaYHumedad() {
  digitalWrite(encendidoSensorHumedadYTemperatura, HIGH);
  // Sensor de temperatura y humedad
  float h = dht.readHumidity();     // Leer humedad
  float t = dht.readTemperature();  // Leer temperatura

  Serial.print("Humedad: ");
  if (isnan(h)) {  // Validación de lectura
    Serial.println("Error al leer la humedad");
  } else {
    Serial.print(h);
    Serial.println(" %");
  }

  Serial.print("Temperatura: ");
  if (isnan(t)) {  // Validación de lectura
    Serial.println("Error al leer la temperatura");
  } else {
    Serial.print(t);
    Serial.println(" °C");
  }
  digitalWrite(encendidoSensorHumedadYTemperatura, LOW);
}

void Ventiladores() {
  //Encender Ventilador por 3 segundos
  digitalWrite(encendidoVentilador, HIGH);
  delay(3000);
  digitalWrite(encendidoVentilador, LOW);
  delay(3000);
}

void LucesUV() {
  //Luces led por 3 segundos
  digitalWrite(encendidoLucesUV, HIGH);
  delay(5000);
  digitalWrite(encendidoLucesUV, LOW);
  delay(5000);
}

// Encender y apagar cada dispositivo durante 3 segundos
void PruebasDeEncendido() {
  digitalWrite(encendidoLucesUV, HIGH);
  delay(3000);
  digitalWrite(encendidoLucesUV, LOW);
  delay(3000);
  digitalWrite(encendidoVentilador, HIGH);
  delay(3000);
  digitalWrite(encendidoVentilador, LOW);
  delay(3000);
  digitalWrite(encendidoSensorHumedadYTemperatura, HIGH);
  delay(3000);
  digitalWrite(encendidoSensorHumedadYTemperatura, LOW);
  delay(3000);
  digitalWrite(encendidoSensorHumedad, HIGH);
  delay(3000);
  digitalWrite(encendidoSensorHumedad, LOW);
  delay(3000);
  digitalWrite(encendidoBombaDeAgua, HIGH);
  delay(3000);
  digitalWrite(encendidoBombaDeAgua, LOW);
  delay(3000);
}