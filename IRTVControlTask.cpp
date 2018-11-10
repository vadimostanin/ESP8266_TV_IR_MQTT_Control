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

uint16_t rawDataJoystickUpButtonDown[19] = {976, 800,  950, 826,  1856, 808,  964, 808,  948, 1694,  966, 810,  1858, 1676,  1818, 1720,  1818, 848,  966};  // RC5 8D4
uint16_t rawDataJoystickUpButtonUp[19] = {976, 802,  974, 804,  1864, 800,  974, 796,  950, 1694,  976, 800,  1864, 1672,  1866, 1670,  1866, 800,  974};  // RC5 8D4

uint16_t rawDataJoystickLeftButtonDown[19] = {938, 842,  932, 842,  1824, 840,  934, 836,  934, 1708,  936, 842,  1824, 1708,  1826, 1708,  1828, 1712,  936};  // RC5 8D5
uint16_t rawDataJoystickLeftButtonUp[19] = {936, 844,  932, 842,  1824, 840,  960, 814,  932, 1706,  938, 842,  1822, 1710,  1828, 1710,  1852, 1686,  936};  // RC5 8D5

uint16_t rawDataBackButtonDown[19] = {936, 840,  936, 840,  1826, 838,  936, 836,  936, 1708,  936, 842,  1826, 838,  936, 1708,  1826, 1710,  1828};  // RC5 8CA
uint16_t rawDataBackButtonUp[19] = {936, 842,  936, 842,  1824, 838,  936, 836,  936, 1708,  936, 840,  1826, 838,  934, 1708,  1826, 1710,  1826};  // RC5 8CA

uint16_t rawDataExitButtonDown[21] = {964, 818,  1822, 842,  958, 814,  932, 840,  930, 1708,  936, 842,  934, 846,  1846, 814,  934, 1706,  1826, 1712,  936};  // RC5 E5
uint16_t rawDataExitButtonUp[21] = {936, 846,  1820, 840,  932, 844,  952, 816,  930, 1708,  962, 820,  932, 846,  1846, 816,  930, 1708,  1854, 1686,  936};  // RC5 E5

uint16_t rawDataMuteButtonDown[21] = {936, 842,  934, 844,  1824, 840,  934, 838,  934, 1708,  936, 842,  1826, 840,  932, 1708,  936, 842,  1824, 1714,  936};  // RC5 8CD
uint16_t rawDataMuteButtonUp[21] = {936, 842,  934, 842,  1824, 840,  934, 840,  928, 1710,  936, 842,  1824, 840,  932, 1708,  960, 818,  1824, 1712,  936};  // RC5 8CD

uint16_t rawDataSamsungPowerOn[135] = {4536, 4440,  620, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  616, 512,  616, 510,  618, 510,  618, 1638,  620, 1638,  618, 1638,  618, 510,  618, 512,  616, 510,  616, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  620, 1638,  618, 510,  616, 510,  616, 1640,  618, 1638,  618, 510,  616, 512,  616, 512,  618, 45958,  4530, 4448,  618, 1640,  618, 1638,  618, 1638,  620, 510,  616, 512,  616, 510,  616, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 510,  618, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1640,  618, 1638,  618, 1638,  618, 510,  618, 512,  616, 1638,  618, 1638,  620, 510,  624, 504,  618, 510,  618};  // SAMSUNG E0E06798

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

IRTVControlTask::IRTVControlTask():
       mIrLed( 4 ), mIrSend( mIrLed ), mSequenceCounter( 0 ), 
       mLoopCounter( 0 ), mIRFrequency( 38 * 1000 ), mLoopsOnYoutubeFromTVScratchCount( 92 ),
       mLoopsOnYoutubeFromTVInitialCount( 1 )
{
  
  mHandler = std::bind( &IRTVControlTask::emptyHandler, this );
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
  mHandler();
}

void IRTVControlTask::setINet( ISubPub * iNet )
{
  mINet = iNet;
}

void IRTVControlTask::emptyHandler()
{
  Serial.print( __FUNCTION__ );Serial.println( " was called" );
}

void IRTVControlTask::setYoutubeFromTVScratchHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleYoutubeFromTVScratch, this );
}

void IRTVControlTask::setYoutubeFromTVInitialHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleYoutubeFromTVInitial, this );
}

void IRTVControlTask::setSamsungPowerHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleTVSamsungPower, this );
}

void IRTVControlTask::handleTVSamsungPower()
{
  Serial.println( "TV Samsung Power On" );
  mIrSend.sendRaw( rawDataSamsungPowerOn, SIZEOF( rawDataSamsungPowerOn ), 38 );
  mINet->publish( "SamsungStatus", "Powered on" );
}

void IRTVControlTask::handleYoutubeFromTVInitial()
{
//  Serial.print( __FUNCTION__ );Serial.println( " was called" );
//  Serial.print( __FUNCTION__ );Serial.println( " leave" );
}

int32_t IRTVControlTask::getLoopsOnYoutubeFromInitialCount()
{
  return mLoopsOnYoutubeFromTVInitialCount;
}

void IRTVControlTask::setMuteHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleMute, this );
}

void IRTVControlTask::setExitHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleExit, this );
}

void IRTVControlTask::setBackHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleBack, this );
}

void IRTVControlTask::setJoystickDownHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleJoystickDown, this );
}

void IRTVControlTask::setJoystickRightHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleJoystickRight, this );
}

void IRTVControlTask::setJoystickUpHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleJoystickUp, this );
}

void IRTVControlTask::setJoystickLeftHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleJoystickLeft, this );
}

void IRTVControlTask::setJoystickEnterHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleJoystickEnter, this );
}

void IRTVControlTask::setPowerHandler()
{
  mHandler = std::bind( &IRTVControlTask::handlePower, this );
}

void IRTVControlTask::setSmartHandler()
{
  mHandler = std::bind( &IRTVControlTask::handleSmart, this );
}

void IRTVControlTask::handleMute()
{
  Serial.println( "TV Mute button down" );
  mIrSend.sendRaw( rawDataMuteButtonDown, SIZEOF( rawDataMuteButtonDown ), 38 );
  delay( 100 );
  Serial.println( "TV Mute button up" );
  mIrSend.sendRaw( rawDataMuteButtonUp, SIZEOF( rawDataMuteButtonUp ), 38 );
}

void IRTVControlTask::handleExit()
{
  Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataExitButtonDown, SIZEOF( rawDataExitButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataExitButtonUp, SIZEOF( rawDataExitButtonUp ), 38 );
}

void IRTVControlTask::handleBack()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataBackButtonDown, SIZEOF( rawDataBackButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataBackButtonUp, SIZEOF( rawDataBackButtonUp ), 38 );
}

void IRTVControlTask::handleJoystickDown()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataJoystickDownButtonDown, SIZEOF( rawDataJoystickDownButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickDownButtonUp, SIZEOF( rawDataJoystickDownButtonUp ), 38 );
}

void IRTVControlTask::handleJoystickRight()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataJoystickRightButtonDown, SIZEOF( rawDataJoystickRightButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickRightButtonUp, SIZEOF( rawDataJoystickRightButtonUp ), 38 );
}

void IRTVControlTask::handleJoystickUp()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataJoystickUpButtonDown, SIZEOF( rawDataJoystickUpButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickUpButtonUp, SIZEOF( rawDataJoystickUpButtonUp ), 38 );
}

void IRTVControlTask::handleJoystickLeft()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataJoystickLeftButtonDown, SIZEOF( rawDataJoystickLeftButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickLeftButtonUp, SIZEOF( rawDataJoystickLeftButtonUp ), 38 );
}

void IRTVControlTask::handleJoystickEnter()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataJoystickEnterButtonDown, SIZEOF( rawDataJoystickEnterButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickEnterButtonUp, SIZEOF( rawDataJoystickEnterButtonUp ), 38 );
}

void IRTVControlTask::handlePower()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataPowerOnButtonDown, SIZEOF( rawDataPowerOnButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataPowerOnButtonUp, SIZEOF( rawDataPowerOnButtonUp ), 38 );
}

void IRTVControlTask::handleSmart()
{
    Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataSmartButtonDown, SIZEOF( rawDataSmartButtonDown ), 38 );
  delay( 100 );
  mIrSend.sendRaw( rawDataSmartButtonUp, SIZEOF( rawDataSmartButtonUp ), 38 );
}

int32_t IRTVControlTask::getLoopsOneCommandCount()
{
  return 1;
}

void IRTVControlTask::handleYoutubeFromTVScratch()
{
//  Serial.printf( "%s was called: this=%p\n", __FUNCTION__, this );
//  Serial.print( "mSequenceCounter=" );Serial.println( mSequenceCounter );
  const int minDelay = 1000;
  mLoopCounter++;
//  Serial.print( "mLoopCounter=" );Serial.println( mLoopCounter );
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
      mDelayTimeSum = 0;
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
      mDelayTimeSum = 0;
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
      mDelayTimeSum = 0;
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

int32_t IRTVControlTask::getLoopsOnYoutubeFromScratchCount()
{
  return mLoopsOnYoutubeFromTVScratchCount;
}

