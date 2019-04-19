#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "ISubPub.h"

#include <map>
class NetworkingTask : public ISubPub
{
public:
  NetworkingTask();

  std::function<void()> getLoop();
  void init();
  PubSubClient& getPubSubClient();
  static void callbackTopic( char* topic, unsigned char* payload, unsigned int length );
  
private:
  void subscribe( const std::string & topic, const std::function<void()> & callback ) override;
  void publish( const std::string & topic, const std::string & message ) override;
  void loopFunc();
  bool connectWiFi();
  void reconnectMQTT();
  void publishPingMQTT();

  WiFiClient wclient;
  PubSubClient mClient;
};

