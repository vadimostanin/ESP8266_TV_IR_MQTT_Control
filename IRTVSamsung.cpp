#include "IRTVSamsung.h"

uint16_t rawDataSamsungPowerOn[135] = {4536, 4440,  620, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  616, 512,  616, 510,  618, 510,  618, 1638,  620, 1638,  618, 1638,  618, 510,  618, 512,  616, 510,  616, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  620, 1638,  618, 510,  616, 510,  616, 1640,  618, 1638,  618, 510,  616, 512,  616, 512,  618, 45958,  4530, 4448,  618, 1640,  618, 1638,  618, 1638,  620, 510,  616, 512,  616, 510,  616, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 510,  618, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1640,  618, 1638,  618, 1638,  618, 510,  618, 512,  616, 1638,  618, 1638,  620, 510,  624, 504,  618, 510,  618};  // SAMSUNG E0E06798

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

IRTVSamsung::IRTVSamsung():
             mIrLed( 4 ), mIrSend( mIrLed ), mSequenceCounter( 0 ), mStatusTopic( "SamsungStatus" )
{
  ;
}

void IRTVSamsung::init()
{
  mIrSend.begin();
}

void IRTVSamsung::resetSequence()
{
  mSequenceCounter = 0;
}

void IRTVSamsung::setINet( std::shared_ptr<ISubPub> iNet )
{
  mINet = iNet;
}

void IRTVSamsung::setChangableHandler( std::shared_ptr<std::function<void()>> handler )
{
  mHandler = handler;
}

int32_t IRTVSamsung::getLoopsOneCommandCount()
{
  return 1;
}

void IRTVSamsung::prepareSamsungPowerHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungPower, this );
}

void IRTVSamsung::handleTVSamsungPower()
{
//  Serial.println( "TV Samsung Power On" );
  mIrSend.sendRaw( rawDataSamsungPowerOn, SIZEOF( rawDataSamsungPowerOn ), 38 );
  mINet->publish( mStatusTopic.c_str(), "Powered on" );
}
