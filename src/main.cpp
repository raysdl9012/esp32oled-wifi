/**
 * Incluir librerias
 * */
#include <Arduino.h>
#include <WiFi.h>
#include "SSD1306Wire.h"

/**
 * Definir variables
 * */
#define LED_OUTPUT 12


/**
 * Variables para WiFi
 * */
const char *ssid = "ssid";
const char *password = "password";

//****************************************
//******* DECLARACION DE FUNCIONES *******
//****************************************

void scanNetworkWiFi();
void connectNetworkWiFi();
String translateEncryptionType(wifi_auth_mode_t encryptionType);


//****************************************
//**************** SETUP *****************
//****************************************

void setup()
{
  Serial.begin(115200);
  pinMode(LED_OUTPUT, OUTPUT);
}

//****************************************
//**************** LOOP ******************
//****************************************
void loop()
{

  if (WiFi.isConnected())
  {
    Serial.println("Connected WiFi");
    Serial.print('IP Network: ');
    Serial.println(WiFi.localIP().toString());
    digitalWrite(LED_OUTPUT, HIGH);

  }
  else
  {
    // Demostracion de scan
    scanNetworkWiFi();
    // Conectar a una red predeterminada
    connectNetworkWiFi();
    digitalWrite(LED_OUTPUT, LOW);
  }
}


//****************************************
//******* DEFINICIÓN FUNCIONES  **********
//****************************************

/**
 * Funcion que se encarga de indicar que tipo de red se detecto
 * */
String translateEncryptionType(wifi_auth_mode_t encryptionType)
{
  switch (encryptionType)
  {
  case (0):
    return "Open";
  case (1):
    return "WEP";
  case (2):
    return "WPA_PSK";
  case (3):
    return "WPA2_PSK";
  case (4):
    return "WPA_WPA2_PSK";
  case (5):
    return "WPA2_ENTERPRISE";
  default:
    return "UNKOWN";
  }
}

/**
 * Funcion que se encarga de escanear las redes para ESP32
 * */
void scanNetworkWiFi()
{
  int numberOfNetworks = WiFi.scanNetworks();
  Serial.println("Result scan: " + (String) numberOfNetworks);
  for (int i = 0; i < numberOfNetworks; i++)
  {
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    //String nameNetwork = WiFi.SSID(i) + "\n" + WiFi.RSSI(i) + "\n" + WiFi.channel(i)  + "\n" + encryptionTypeDescription;
    String nameNetwork = WiFi.SSID(i) + "\n" + encryptionTypeDescription;
    Serial.println(nameNetwork);
    delay(3000);
  }
}

/**
 * Funcion que se encarga de conextarse a una red WiFi
 * */
void connectNetworkWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Estado Wifi" + WiFi.status());
  }
}

