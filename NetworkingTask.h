#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <map>
class NetworkingTask
{
public:
  NetworkingTask();

  void operator()();
  void addListener( const std::string & topic, const std::function<void()> & callback );
  void init();
  PubSubClient& getPubSubClient();
//  void operator()( char* topic, unsigned char* payload, unsigned int length );
  static void callbackTopic( char* topic, unsigned char* payload, unsigned int length );
  
private:
  bool connectWiFi();
  void reconnectMQTT();
  void publishPingMQTT();

  WiFiClient wclient;
  PubSubClient mClient;
};

