/*
   Para este proyecto estoy utilizando un 'NodeMCU V3 ESP8266' con dos LEDS y un pulsador.
   El objetivo de este sketch es el de enviar un 'paquete mágico' para encender un ordenador
   de manera remota (que además esté conectado vía cable al router).
   Es necesario que el motherboard tenga activado en el BIOS la opción 'Wake on Lan'.
   Más información y entrada completa en: https://thenerdyapprentice.blogspot.com/
*/

#include "ESP8266WiFi.h"
#include <WiFiUdp.h>
#include <WakeOnLan.h>
#include <Debouncer.h> // Librería debouncer para el pulsador de: https://github.com/hideakitai/Debouncer

WiFiUDP UDP; // Inicializamos la clase WiFIUDP
WakeOnLan WOL(UDP); // Iniciamos la clase WakeOnLan

//Agregamos los datos de conexión
const char* ssid = "AQUI-LA-SSID"; // SSID de la red a la que nos queremos conectar
const char* password = "AQUI-EL-PASSWORD"; // Password de la misma
const char* MACAdress = "E0-3D-13-26-AC-E6"; // Dirección MAC de la placa de red de la pc que encenderemos.

const int ledG = D5;
const int ledB = D6;
const int PUSH = D2;
int duracion_ms = 50; // Duración del tiempo de debounce para el pulsador

Debouncer debouncer(PUSH, duracion_ms); // Inicializamos el objeto debouncer

void setup() {

  pinMode(PUSH, INPUT_PULLUP);

  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  digitalWrite(ledG, LOW); // Inicializamos los LED en LOW
  digitalWrite(ledB, LOW);

  Serial.begin(115200); // Iniciamos el puerto serie
  WiFi.begin(ssid, password); // Conectamos a la red
  WiFi.mode(WIFI_STA);// Modo cliente

  // Esperamos hasta conectarnos
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    digitalWrite(ledB, HIGH); // Encendemos el LED azul para indicar que estamos intentando conectarnos
    delay(200);
  }

  Serial.println();
  // Si la conexión es exitosa, mostramos la IP por el puerto serie,
  // apagamos el LED azul y encendemos el verde indicando que la conexión fue exitosa

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(ledB, LOW);
    digitalWrite(ledG, HIGH);
    Serial.print("Conectado, dirección IP: ");
    Serial.println(WiFi.localIP());
    // Esperamos un segundo y medio y apagamos el LED verde
    delay(1500);
    digitalWrite(ledG, LOW);
  }

  WOL.setRepeat(3, 100); // Repetimos el paquete tres veces con 100ms de delay.
  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()); // Calculamos y sateamos la dirección de broadcast
  // WOL.setBroadAddress("192.168.1.255") Si quisieramos hacer el paso anterior de manera manual

  // Mostramos por el puerto serie
  Serial.print("Dirección de broadcast: ");
  Serial.println(WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask()));

}

void loop() {
  debouncer.update();

  if (debouncer.falling()) { // Cuando presionamos el pulsador
    // Enviamos paquete WOL (puerto 9 por defecto) Utilizamos el LED verde como indicador
    Serial.println("Enviando paquete WOL.");
    digitalWrite(ledG, HIGH);
    WOL.sendMagicPacket(MACAdress);
    delay(1000);
    digitalWrite(ledG, LOW);
  }

}
