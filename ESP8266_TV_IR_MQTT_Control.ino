/*
 * IRremoteESP8266: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * This is very simple teaching code to show you how to use the library.
 * If you are trying to decode your Infra-Red remote(s) for later replay,
 * use the IRrecvDumpV2.ino example code instead of this.
 * An IR detector/demodulator must be connected to the input kRecvPin.
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 * Example circuit diagram:
 *  https://github.com/markszabo/IRremoteESP8266/wiki#ir-receiving
 * Changes:
 *   Version 0.2 June, 2017
 *     Changed GPIO pin to the same as other examples.
 *     Used our own method for printing a uint64_t.
 *     Changed the baud rate to 115200.
 *   Version 0.1 Sept, 2015
 *     Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
//#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "laptop"; // Имя вайфай точки доступа
const char *pass = "q1w2e3r4"; // Пароль от точки доступа

const char *mqtt_server = "m21.cloudmqtt.com"; // Имя сервера MQTT
const char *mqtt_key = "95bb79e8-0e73-469a-b799-01cc5dcbede4";
const int mqtt_port = 13969; // Порт для подключения к серверу MQTT
const char *mqtt_user = "xtdtvxau"; // Логи от сервер
const char *mqtt_pass = "C0f1bz0V2Zrz"; // Пароль от сервера
const char *mqtt_topic_tv_hitach_youtube_on = "tv_hitachi_youtube_on";

uint16_t rawDataPowerOnButtonDown[21] = {936, 842,  934, 840,  1826, 838,  934, 838,  934, 1708,  936, 826,  1842, 838,  934, 1708,  936, 844,  1822, 840,  934};  // RC5 8CC
uint16_t rawDataPowerOnButtonUp[21] = {938, 842,  932, 844,  1824, 840,  932, 840,  932, 1708,  936, 844,  1824, 842,  932, 1708,  936, 842,  1848, 816,  934};  // RC5 8CC

uint16_t rawDataSmartButtonDown[21] = {926, 850,  1856, 808,  966, 804,  968, 806,  966, 1676,  928, 848,  968, 808,  1858, 1678,  968, 808,  926, 850,  1858};  // RC5 EE
uint16_t rawDataSmartButtonUp[21] = {928, 848,  1816, 848,  926, 846,  924, 848,  924, 1718,  926, 850,  926, 852,  1814, 1720,  924, 852,  924, 852,  1814};  // RC5 EE

uint16_t rawDataJoystickDownButtonDown[21] = {960, 816,  1850, 814,  960, 810,  960, 812,  958, 1684,  960, 816,  1850, 1686,  1854, 810,  960, 1682,  962, 818,  960};  // RC5 D3
uint16_t rawDataJoystickDownButtonUp[21] = {978, 800,  1866, 796,  978, 792,  976, 796,  978, 1666,  978, 798,  1868, 1668,  1868, 798,  976, 1668,  974, 804,  976};  // RC5 D3

uint16_t rawDataJoystickRightButtonDown[19] = {982, 796,  978, 794,  1874, 790,  982, 788,  984, 1660,  984, 794,  1872, 1664,  1872, 1664,  980, 794,  1872};  // RC5 8D6
uint16_t rawDataJoystickRightButtonUp[19] = {946, 828,  950, 826,  1840, 824,  948, 824,  948, 1696,  978, 798,  1840, 1696,  1840, 1698,  948, 828,  1838};  // RC5 8D6

uint16_t rawDataJoystickEnterButtonDown[21] = {940, 836,  1830, 832,  942, 834,  938, 832,  944, 1702,  936, 838,  942, 834,  938, 840,  1828, 1704,  1828, 1710,  942};  // RC5 F5
uint16_t rawDataJoystickEnterButtonUp[21] = {950, 830,  1828, 838,  936, 834,  940, 828,  944, 1700,  942, 834,  940, 836,  942, 834,  1832, 1706,  1830, 1704,  942};  // RC5 F5

WiFiClient wclient;
PubSubClient client(mqtt_server, mqtt_port, wclient);

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
//const uint16_t kRecvPin = 14;

//IRrecv irrecv( kRecvPin );

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

decode_results results;

bool connectWiFi();
void reconnectMQTT();
void handleIRInput();
void callbackMQTT(char* topic, byte* payload, unsigned int length);

void setup()
{
  Serial.begin( 9600 );
//  irrecv.enableIRIn();  // Start the receiver
  irsend.begin();
  while( ! Serial )  // Wait for the serial connection to be establised.
  {
    delay( 100 );
  }
  Serial.println();
//  Serial.print( "IRrecvDemo is now running and waiting for IR message on Pin " );
//  Serial.println( kRecvPin );
  connectWiFi();
  client.setCallback( callbackMQTT );
}
int counter = 0;
long lastMsg = 0;
char msg[50];

void loop()
{
  if( !client.connected() )
  {
    reconnectMQTT();
  }
  client.loop();

  long now = millis();
  if( ( now - lastMsg ) > 5000 )
  {
    lastMsg = now;
    ++counter;
    snprintf( msg, 50, "hello world #%ld", counter );
    Serial.print( "Publish message: " );
    Serial.println( msg );
    client.publish( "outTopic", msg );
  }
  
//  handleIRInput();
  delay( 100 );
}
/*
void handleIRInput()
{
  if( irrecv.decode( &results ) )
  {
    String sResult = resultToHumanReadableBasic( &results );
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64( results.value, HEX );
    Serial.println("");
    Serial.print( sResult );
//    irrecv.resume();  // Receive the next value
  }
}
*/

bool connectWiFi()
{
  bool result = false;
  // подключаемся к wi-fi
  if( WiFi.status() != WL_CONNECTED )
  {
    Serial.print( "Connecting to " );
    Serial.print( ssid );
    Serial.println( "..." );
    WiFi.begin( ssid, pass );
    
    result = WiFi.waitForConnectResult() == WL_CONNECTED;

    if( result )
    {
      Serial.println( "WiFi connected" );
    }
    else
    {
      Serial.println( "WiFi can't be connected" );
    }
  }
  return result;
}

void callbackMQTT(char* topic, byte* payload, unsigned int length)
{
  Serial.print( "Message arrived [" );
  Serial.print( topic );
  Serial.print( "] " );
  for( int i = 0 ; i < length ; i++ )
  {
    Serial.print( ( char ) payload[i] );
  }
  Serial.println();
  if( strcmp( topic, mqtt_topic_tv_hitach_youtube_on ) == 0 )
  {
    Serial.print( "SEND sequence of IR commands" );
    Serial.println();
    ;//SEND sequence of IR commands
    irsend.sendRaw( rawDataPowerOnButtonDown, 67, 38 );
    delay( 100 );
    irsend.sendRaw( rawDataPowerOnButtonUp, 67, 38 );
  }
}

void reconnectMQTT()
{
  // Loop until we're reconnected
  while( !client.connected() )
  {
    Serial.print( "Attempting MQTT connection..." );
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String( random( 0xffff ), HEX );
    // Attempt to connect
    if( client.connect( mqtt_key, mqtt_user, mqtt_pass ) )
    {
      Serial.println( "connected" );
      // Once connected, publish an announcement...
      client.publish( "outTopic", "hello world" );
      // ... and resubscribe
      client.subscribe( "inTopic" );
      client.subscribe( mqtt_topic_tv_hitach_youtube_on );
    }
    else
    {
      Serial.print( "failed, rc=" );
      Serial.print( client.state() );
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}

