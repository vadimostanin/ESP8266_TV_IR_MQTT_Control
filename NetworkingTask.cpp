#include "NetworkingTask.h"
#include <functional> // for bind() 

const char *ssid = "laptop"; // Имя вайфай точки доступа
const char *pass = "q1w2e3r4"; // Пароль от точки доступа

const char *mqtt_server = "m21.cloudmqtt.com"; // Имя сервера MQTT
const char *mqtt_key = "95bb79e8-0e73-469a-b799-01cc5dcbede4";
const int mqtt_port = 13969; // Порт для подключения к серверу MQTT
const char *mqtt_user = "xtdtvxau"; // Логи от сервер
const char *mqtt_pass = "C0f1bz0V2Zrz"; // Пароль от сервера

namespace
{
  std::map<std::string, std::function<void()>> mConcreteTopicListeners;
  std::vector<std::function<void(std::string)>> mAnyTopicListeners;
}

NetworkingTask::NetworkingTask() : mClient( mqtt_server, mqtt_port, wclient )
{
}

void NetworkingTask::init()
{
  connectWiFi();
  mClient.setCallback( std::bind( &NetworkingTask::callbackTopic, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );
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
  const auto foundListenerIter = mConcreteTopicListeners.find( topic );
  if( foundListenerIter != std::end( mConcreteTopicListeners ) )
  {
    foundListenerIter->second();
  }
  else
  {
    Serial.print( "Topic \""); Serial.print( topic ); Serial.println( "\" not found" );
  }
  for( const auto anyTopicListener : mAnyTopicListeners )
  {
    anyTopicListener( topic );
  }
}

void NetworkingTask::publishPingMQTT()
{
  const long now = millis();
  static long lastMsg = now;
  if( ( now - lastMsg ) > 5000 )
  {
    lastMsg = now;
    static char msg[50];
    static int counter = 0;
    ++counter;
    snprintf( msg, 50, "ping #%ld", counter );
    Serial.print( "Publish message: " );
    Serial.println( msg );
    mClient.publish( "pingTopic", msg );

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
      for( auto & topic : mConcreteTopicListeners )
      {
        Serial.print( "Subscribing to " );Serial.println( topic.first.c_str() );
        mClient.subscribe( topic.first.c_str() );
        mClient.loop();
      }
    }
    else
    {
//      Serial.print( "failed, rc=" );
//      Serial.print( mClient.state() );
//      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}

void NetworkingTask::subscribe( const std::string & topic, const std::function<void()> & callback )
{
  Serial.print( "add topic.c_str()=" );
  Serial.print( topic.c_str() );
  Serial.println( " to queue" );
  auto foundListenerIter = mConcreteTopicListeners.find( topic );
  if( foundListenerIter == std::end( mConcreteTopicListeners ) )
  {
    mConcreteTopicListeners[topic] = callback;
    if( mClient.connected() )
    {
//      Serial.print( "mqtt server is connected, subscribe topic.c_str()=" );
//      Serial.println( topic.c_str() );
      mClient.subscribe( topic.c_str() );
    }
  }
  else
  {
//    Serial.print( "Topic \"" );
//    Serial.print( topic.c_str() );
//    Serial.println( "\" was subscribed already." );
  }
}

void NetworkingTask::subscribe( const std::function<void(std::string)> & callback )
{
  mAnyTopicListeners.push_back( callback );
}

void NetworkingTask::publish( const std::string & topic, const std::string & message )
{
  mClient.publish( topic.c_str(), message.c_str() );
}

