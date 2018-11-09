#include "NetworkingTask.h"

const char *ssid = "laptop"; // Имя вайфай точки доступа
const char *pass = "q1w2e3r4"; // Пароль от точки доступа

const char *mqtt_server = "m21.cloudmqtt.com"; // Имя сервера MQTT
const char *mqtt_key = "95bb79e8-0e73-469a-b799-01cc5dcbede4";
const int mqtt_port = 13969; // Порт для подключения к серверу MQTT
const char *mqtt_user = "xtdtvxau"; // Логи от сервер
const char *mqtt_pass = "C0f1bz0V2Zrz"; // Пароль от сервера

std::map<std::string, std::function<void()>> mListeners;

NetworkingTask::NetworkingTask() : mClient( mqtt_server, mqtt_port, wclient )
{
}

void NetworkingTask::init()
{
  connectWiFi();
//  mClient.setCallback( std::bind( &NetworkingTask::callbackMQTT, this ) );
//  mClient.setCallback( *this );
  mClient.setCallback( callbackTopic );
}
PubSubClient & NetworkingTask::getPubSubClient()
{
  return mClient;
}

void NetworkingTask::loopFunc()
{
  if( !mClient.connected() )
  {
    reconnectMQTT();
  }

  if( mClient.connected() )
  {
    publishPingMQTT();
  }

  delay( 200 );
};
  
std::function<void()> NetworkingTask::getLoop()
{
  auto func = [this](){ loopFunc(); };
  return std::bind( func );
}

bool NetworkingTask::connectWiFi()
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

void NetworkingTask::callbackTopic(char* topic, unsigned char* payload, unsigned int length)
{
  Serial.print( "Message arrived [" );
  Serial.print( topic );
  Serial.print( "] " );
  for( int i = 0 ; i < length ; i++ )
  {
    Serial.print( ( char ) payload[i] );
  }
  Serial.println();
  auto foundListenerIter = mListeners.find( topic );
  if( foundListenerIter != std::end( mListeners ) )
  {
    foundListenerIter->second();
  }
  else
  {
    Serial.print( "Topic \""); Serial.print( topic ); Serial.println( "\" not found" );
  }
}

void NetworkingTask::publishPingMQTT()
{
  long now = millis();
  static long lastMsg = now;
  if( ( now - lastMsg ) > 5000 )
  {
    lastMsg = now;
    static char msg[50];
    static int counter = 0;
    ++counter;
    snprintf( msg, 50, "hello world #%ld", counter );
    Serial.print( "Publish message: " );
    Serial.println( msg );
    mClient.publish( "outTopic", msg );

    // Once connected, publish an announcement...
//    mClient.publish( "inTopic", "incomming message" );
  }
}

void NetworkingTask::reconnectMQTT()
{
  Serial.print( "NetworkingTask mClient.connected()=" );Serial.println( mClient.connected() );
  // Loop until we're reconnected
  if( !mClient.connected() )
  {
    Serial.print( "Attempting MQTT connection..." );
    // Attempt to connect
    if( mClient.connect( mqtt_key, mqtt_user, mqtt_pass ) )
    {
      Serial.println( "connected" );
      // ... and resubscribe
      mClient.subscribe( "inTopic" );
      for( auto & topic : mListeners )
      {
        Serial.print( "Subscribing to " );Serial.println( topic.first.c_str() );
        mClient.subscribe( topic.first.c_str() );
      }
    }
    else
    {
      Serial.print( "failed, rc=" );
      Serial.print( mClient.state() );
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}

void NetworkingTask::addListener( const std::string & topic, const std::function<void()> & callback )
{
  Serial.print( "addListener topic.c_str()=" );
  Serial.println( topic.c_str() );
  mClient.subscribe( topic.c_str() );
  mListeners[topic] = callback;
}

