#include "IRTVSamsung.h"

uint16_t rawDataSamsungPowerOn[135] = {4536, 4440,  620, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  616, 512,  616, 510,  618, 510,  618, 1638,  620, 1638,  618, 1638,  618, 510,  618, 512,  616, 510,  616, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  620, 1638,  618, 510,  616, 510,  616, 1640,  618, 1638,  618, 510,  616, 512,  616, 512,  618, 45958,  4530, 4448,  618, 1640,  618, 1638,  618, 1638,  620, 510,  616, 512,  616, 510,  616, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 510,  618, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1640,  618, 1638,  618, 1638,  618, 510,  618, 512,  616, 1638,  618, 1638,  620, 510,  624, 504,  618, 510,  618};  // SAMSUNG E0E06798

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

IRTVSamsung::IRTVSamsung(): IRTVBase( 4 ), mStatusTopic( "SamsungStatus" )
{
  ;
}

int32_t IRTVSamsung::getLoopsOneCommandCount()
{
  return 1;
}

void IRTVSamsung::prepareSamsungPowerHandler()
{
  Serial.println( "prepareSamsungPowerHandler 1" );
  resetSequence();
  Serial.println( "prepareSamsungPowerHandler 1" );
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungPower, this );
  Serial.println( "prepareSamsungPowerHandler 1" );
}

void IRTVSamsung::handleTVSamsungPower()
{
  Serial.println( "TV Samsung Power On" );
  mIrSend.sendRaw( rawDataSamsungPowerOn, SIZEOF( rawDataSamsungPowerOn ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "Powered on" );
}
