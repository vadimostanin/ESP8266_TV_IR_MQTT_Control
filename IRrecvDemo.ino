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
#include <IRrecv.h>
#include <IRutils.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "VIBE"; // Имя вайфай точки доступа
const char *pass = "q1w2e3r4"; // Пароль от точки доступа

const char *mqtt_server = "m21.cloudmqtt.com"; // Имя сервера MQTT
const char *mqtt_key = "95bb79e8-0e73-469a-b799-01cc5dcbede4";
const int mqtt_port = 13969; // Порт для подключения к серверу MQTT
const char *mqtt_user = "xtdtvxau"; // Логи от сервер
const char *mqtt_pass = "C0f1bz0V2Zrz"; // Пароль от сервера
const char *mqtt_topic_tv_hitach_youtube_on = "tv_hitachi_youtube_on";

uint16_t rawDataSomeCommand[71] = {9018, 4544,  506, 588,  534, 576,  506, 588,  504, 598,  504, 1708,  506, 598,  504, 598,  504, 588,  506, 1698,  532, 1672,  506, 1698,  506, 1708,  506, 588,  530, 1674,  506, 1698,  506, 1708,  506, 588,  504, 598,  506, 1708,  506, 590,  504, 1708,  506, 588,  506, 606,  504, 588,  504, 1700,  504, 1698,  506, 596,  506, 1708,  506, 588,  506, 1698,  506, 1698,  506, 1708,  506, 39924,  9020, 2276,  506};  // NEC 8F728D7

WiFiClient wclient; 
PubSubClient client(mqtt_server, mqtt_port, wclient);

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
const uint16_t kRecvPin = 14;

IRrecv irrecv( kRecvPin );

decode_results results;

bool connectWiFi();
void reconnectMQTT();
void handleIRInput();
void callbackMQTT(char* topic, byte* payload, unsigned int length);

void setup()
{
  Serial.begin( 9600 );
  irrecv.enableIRIn();  // Start the receiver
  while( ! Serial )  // Wait for the serial connection to be establised.
  {
    delay( 100 );
  }
  Serial.println();
  Serial.print( "IRrecvDemo is now running and waiting for IR message on Pin " );
  Serial.println( kRecvPin );
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
  
  handleIRInput();
  delay( 100 );
}

void handleIRInput()
{
  if( irrecv.decode( &results ) )
  {
    String sResult = resultToHumanReadableBasic( &results );
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64( results.value, HEX );
    Serial.println("");
    Serial.print( sResult );
    irrecv.resume();  // Receive the next value
  }
}

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

