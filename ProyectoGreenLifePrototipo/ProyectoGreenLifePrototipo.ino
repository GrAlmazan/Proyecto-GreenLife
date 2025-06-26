//Librerias necesarias
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Pantalla para sensores y tanque
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensores DHT de Temperatura y Humedad
#define DHTPIN1 12
#define DHTPIN2 13
#define DHTTYPE DHT21
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// Pines del arduino
const int sensorHumedadSuelo1Pin = A0;
const int sensorHumedadSuelo2Pin = A1;
const int sensorNivelTanquePin = A2;

const int abanicoIzquierdoPin = 2;
const int abanicoDerechoPin = 3;
const int bombaDeAguaPin = 4;
const int ledRojoPin = 5;
const int ledAzulPin = 6;
const int sensorDeHumedad1 = 7; //
const int sensorDeHumedad2 = 8; //
const int sensorTemperatura = 9;
const int sensorTemperatura2 = 10;

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("INICIANDO ...");
  lcd.setCursor(0, 1);
  lcd.print("GREEN LIFE");
  delay(2000);
  lcd.clear();

  pinMode(sensorHumedadSuelo1Pin, INPUT);
  pinMode(sensorHumedadSuelo2Pin, INPUT);
  pinMode(sensorNivelTanquePin, INPUT);

  pinMode(abanicoIzquierdoPin, OUTPUT);
  pinMode(abanicoDerechoPin, OUTPUT);
  pinMode(bombaDeAguaPin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);
  pinMode(ledAzulPin, OUTPUT);
  pinMode(sensorDeHumedad1, OUTPUT);
  pinMode(sensorDeHumedad2, OUTPUT);
  pinMode(sensorTemperatura, OUTPUT);
  pinMode(sensorTemperatura2, OUTPUT);


  digitalWrite(abanicoIzquierdoPin, LOW);
  digitalWrite(abanicoDerechoPin, LOW);
  digitalWrite(bombaDeAguaPin, LOW);
  digitalWrite(ledRojoPin, LOW);
  digitalWrite(ledAzulPin, LOW);
  digitalWrite(sensorDeHumedad1, LOW);
  digitalWrite(sensorDeHumedad2, LOW);
  digitalWrite(sensorTemperatura, LOW);
  digitalWrite(sensorTemperatura2, LOW);

  Serial.println("Sistema iniciado");
  Serial.println("Iniciando Void Loop");
}

void loop() {
  MostrarNivelTanqueEnLCD();
  delay(6000);

  MostrarSensoresDHT();
  delay(6000);

  MostrarSensorDeHumedadSuelo();
  delay(6000);

  ControlarClima();
  delay(6000);
}

// Humedad de suelo
void MostrarSensorDeHumedadSuelo() {
  //Encender Sensores
  EncenderSensoresSuelo();

  int humedad1 = analogRead(sensorHumedadSuelo1Pin);
  int humedad2 = analogRead(sensorHumedadSuelo2Pin);

  // Mostrar en la pantalla LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H.T1:");
  lcd.print(humedad1);
  lcd.print("H.T2:");
  lcd.print(humedad2);

  lcd.setCursor(0, 1);
  if (humedad1 < 500 || humedad2 < 500) {
    lcd.print("Riego Activado");
    Serial.println("Humedad baja: activando bomba...");
    //EncenderBombaDeAgua();
    //delay(23000); // 500 mililitros 80litrosX1hora
    ApagarBombaDeAgua();
  } else {
    lcd.print("Humedad OK");
    Serial.println("Humedad adecuada.");
    ApagarBombaDeAgua();
  }
  // Apagar sensores 
  ApagarSensoresSuelo();
}

// Mostrar nivel de tanque en pantalla 0x27
void MostrarNivelTanqueEnLCD() {
  int valor = analogRead(sensorNivelTanquePin);
  lcd.clear();
  delay(100);

  lcd.setCursor(0, 0);
  lcd.print("Tanque: ");
  lcd.print(valor);

  lcd.setCursor(0, 1);
  lcd.print("Nivel: ");
  if (valor == 0) {
    lcd.print("Bajo ");
  } else if (valor > 1 && valor < 350) {
    lcd.print("Bajo  ");
  } else if (valor >= 350 && valor < 510) {
    lcd.print("Medio ");
  } else if (valor >= 510) {
    lcd.print("Alto  ");
  }

  Serial.print("Nivel tanque: ");
  Serial.println(valor);
}

// Mostrar sensores DHT en pantalla 0x27
void MostrarSensoresDHT() {
  EncenderSensoresDHT();

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  lcd.clear();
  delay(100);

  lcd.setCursor(0, 0);
  lcd.print("T1:");
  lcd.print(t1, 1);
  lcd.print(" H1:");
  lcd.print(h1, 0);

  lcd.setCursor(0, 1);
  lcd.print("T2:");
  lcd.print(t2, 1);
  lcd.print(" H2:");
  lcd.print(h2, 0);

  Serial.print("T1: "); Serial.print(t1); Serial.print(" H1: "); Serial.println(h1);
  Serial.print("T2: "); Serial.print(t2); Serial.print(" H2: "); Serial.println(h2);
  
  ApagarSensoresDHT();
}

void ControlarClima() {
  EncenderSensoresDHT(); // Encender sensores de temperatura/humedad

  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();
  float promedioTemp = (t1 + t2) / 2.0;

  Serial.print("Temperatura promedio: ");
  Serial.println(promedioTemp);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. Promedio:");
  lcd.setCursor(0, 1);
  lcd.print(promedioTemp);
  delay(3000);

  // Condición: temperatura baja (simula noche)
  if (promedioTemp < 22.0) {
    Serial.println("Temp baja - Activando luces UV, apagando ventiladores.");

    EncenderLuces();
    ApagarVentiladores();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ENCENDIENDO");
    lcd.setCursor(0, 1);
    lcd.print("LUZ UV");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APAGANDO");
    lcd.setCursor(0, 1);
    lcd.print("VENTILADORES");
    delay(1000);
  }

  // Condición: temperatura alta
  else if (promedioTemp > 28.0) {
    Serial.println("Temp alta - Activando ventiladores, apagando luces UV.");

    ApagarLuces();
    EncenderVentiladores();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ENCENDIENDO");
    lcd.setCursor(0, 1);
    lcd.print("VENTILADORES");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APAGANDO");
    lcd.setCursor(0, 1);
    lcd.print("LUZ UV");
    delay(1000);
  }

  // Condición: temperatura normal
  else {
    Serial.println("Temp normal - Apagando luces UV y ventiladores.");

    ApagarLuces();
    ApagarVentiladores();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP. ESTABLE");
    lcd.setCursor(0, 1);
    lcd.print("TODO EN OFF");
    delay(1000);
  }

  ApagarSensoresDHT(); // Apagar sensores al terminar
}

// ! Funciones de Encendido y Apagado ------------------------
// Bomba
void EncenderBombaDeAgua() {
  digitalWrite(bombaDeAguaPin, HIGH);
}

void ApagarBombaDeAgua() {
  digitalWrite(bombaDeAguaPin, LOW);
}

// Ventiladores
void EncenderVentiladores() {
  digitalWrite(abanicoIzquierdoPin, HIGH);
  digitalWrite(abanicoDerechoPin, HIGH);
}

void ApagarVentiladores() {
  digitalWrite(abanicoIzquierdoPin, LOW);
  digitalWrite(abanicoDerechoPin, LOW);
}

// Luces
void EncenderLuces() {
  digitalWrite(ledRojoPin, HIGH);
  digitalWrite(ledAzulPin, HIGH);
}

void ApagarLuces() {
  digitalWrite(ledRojoPin, LOW);
  digitalWrite(ledAzulPin, LOW);
}

// Sensores de Suelo
void EncenderSensoresSuelo(){
  digitalWrite(sensorDeHumedad1, HIGH);
  digitalWrite(sensorDeHumedad2, HIGH);
}

void ApagarSensoresSuelo(){
  digitalWrite(sensorDeHumedad1, LOW);
  digitalWrite(sensorDeHumedad2, LOW);
}

// Sensores de Ambiente
void EncenderSensoresDHT(){
  digitalWrite(sensorTemperatura, HIGH);
  digitalWrite(sensorTemperatura2, HIGH);
}

void ApagarSensoresDHT(){
  digitalWrite(sensorTemperatura, LOW);
  digitalWrite(sensorTemperatura2, LOW);
}