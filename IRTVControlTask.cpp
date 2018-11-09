#include "IRTVControlTask.h"

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

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

IRTVControlTask::IRTVControlTask() : mIrLed( 4 ), mIrSend( mIrLed ), mSequenceCounter( 0 ), mLoopCounter( 0 )
{
}

void IRTVControlTask::init()
{
  mIrSend.begin();
}

void IRTVControlTask::resetSequence()
{
  mSequenceCounter = 0;
}

void IRTVControlTask::operator()()
{
//  Serial.print( "mSequenceCounter=" );Serial.println( mSequenceCounter );
  const int minDelay = 1000;
  mLoopCounter++;
  Serial.print( "mLoopCounter=" );Serial.println( mLoopCounter );
  switch( mSequenceCounter )
  {
    case 0:
    {
      Serial.println( "TV Powering-on button down" );
      mIrSend.sendRaw( rawDataPowerOnButtonDown, SIZEOF( rawDataPowerOnButtonDown ), 38 );
      delay( 100 );
      Serial.println( "TV Powering-on button up" );
      mIrSend.sendRaw( rawDataPowerOnButtonUp, SIZEOF( rawDataPowerOnButtonUp ), 38 );

      mSequenceCounter++;

      break;
    }
    case 1:
    {
      Serial.println( "TV Wait after TV was powered-on" );
      mSequenceCounter++;
      break;
    }
    case 2:
    {
//      Serial.print( "mDelayTimeSum=" );Serial.println( mDelayTimeSum );
      delay( minDelay );
      mDelayTimeSum += minDelay;
      if( mDelayTimeSum > 30 * 1000 )
      {
//        Serial.println( "if( mDelayTimeSum > 300 * minDelay )" );
        mDelayTimeSum = 0;
        mSequenceCounter++;
      }
      break;
    }
    case 3:
    {  
      Serial.println( "TV Smart launching button down" );
      mIrSend.sendRaw( rawDataSmartButtonDown, SIZEOF( rawDataSmartButtonDown ), 38 );
      delay( 100 );
      Serial.println( "TV Smart launching button up" );
      mIrSend.sendRaw( rawDataSmartButtonUp, SIZEOF( rawDataSmartButtonUp ), 38 );

      mSequenceCounter++;
      break;
    }
    case 4:
    {
      Serial.println( "TV Wait after smart was launched" );
      mSequenceCounter++;
      break;
    }
    case 5:
    {
//      Serial.print( "mDelayTimeSum=" );Serial.println( mDelayTimeSum );
      delay( minDelay );
      mDelayTimeSum += minDelay;
      if( mDelayTimeSum > 30 * 1000 )
      {
        mDelayTimeSum = 0;
        mSequenceCounter++;
      }
      break;
    }
    case 6:
    {
      Serial.println( "TV navigating to youtube begin" );
      mSequenceCounter++;
      break;
    }
    case 7:
    case 9:
    case 11:
    case 13:
    {
      Serial.println( "TV navigating down" );
      mIrSend.sendRaw( rawDataJoystickDownButtonDown, SIZEOF( rawDataJoystickDownButtonDown ), 38 );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickDownButtonUp, SIZEOF( rawDataJoystickDownButtonUp ), 38 );
      mSequenceCounter++;
      mDelayTimeSum = 0;
      break;
    }
    case 8:
    case 10:
    case 12:
    case 14:
    {
      delay( minDelay );
      mDelayTimeSum += minDelay;
      if( mDelayTimeSum > 1 * 1000 )
      {
        mDelayTimeSum = 0;
        mSequenceCounter++;
      }
      break;
    }
    case 15:
    case 17:
    case 19:
    {
      Serial.println( "TV navigating right" );
      mIrSend.sendRaw( rawDataJoystickRightButtonDown, SIZEOF( rawDataJoystickRightButtonDown ), 38 );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickRightButtonUp, SIZEOF( rawDataJoystickRightButtonUp ), 38 );
      mSequenceCounter++;
      break;
    }
    case 16:
    case 18:
    case 20:
    {
      delay( minDelay );
      mDelayTimeSum += minDelay;
      if( mDelayTimeSum > 1 * 1000 )
      {
        mDelayTimeSum = 0;
        mSequenceCounter++;
      }
      break;
    }
    case 21:
    {
      Serial.println( "TV navigating to youtube finished" );
      mSequenceCounter++;
      break;
    }
    case 22:
    {
      Serial.println( "TV Joystick pressing on Youtube icon" );
      mIrSend.sendRaw( rawDataJoystickEnterButtonDown, SIZEOF( rawDataJoystickEnterButtonDown ), 38 );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickEnterButtonUp, SIZEOF( rawDataJoystickEnterButtonUp ), 38 );
      mSequenceCounter++;
      break;
    }
    case 23:
    {
      Serial.println( "TV Youtube shoulbe launched" );
      mSequenceCounter++;
      break;
    }
    case 24:
    {
      mSequenceCounter = 0;
    }
  }
}
