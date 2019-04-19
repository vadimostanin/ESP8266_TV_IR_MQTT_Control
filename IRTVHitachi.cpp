#include "IRTVHitachi.h"

uint16_t rawDataPowerOnButtonDown[] = {936, 842,  934, 840,  1826, 838,  934, 838,  934, 1708,  936, 826,  1842, 838,  934, 1708,  936, 844,  1822, 840,  934};  // RC5 8CC
uint16_t rawDataPowerOnButtonUp[] = {938, 842,  932, 844,  1824, 840,  932, 840,  932, 1708,  936, 844,  1824, 842,  932, 1708,  936, 842,  1848, 816,  934};  // RC5 8CC

uint16_t rawDataSmartButtonDown[] = {926, 850,  1856, 808,  966, 804,  968, 806,  966, 1676,  928, 848,  968, 808,  1858, 1678,  968, 808,  926, 850,  1858};  // RC5 EE
uint16_t rawDataSmartButtonUp[] = {928, 848,  1816, 848,  926, 846,  924, 848,  924, 1718,  926, 850,  926, 852,  1814, 1720,  924, 852,  924, 852,  1814};  // RC5 EE

uint16_t rawDataJoystickDownButtonDown[] = {960, 816,  1850, 814,  960, 810,  960, 812,  958, 1684,  960, 816,  1850, 1686,  1854, 810,  960, 1682,  962, 818,  960};  // RC5 D3
uint16_t rawDataJoystickDownButtonUp[] = {978, 800,  1866, 796,  978, 792,  976, 796,  978, 1666,  978, 798,  1868, 1668,  1868, 798,  976, 1668,  974, 804,  976};  // RC5 D3

uint16_t rawDataJoystickRightButtonDown[] = {982, 796,  978, 794,  1874, 790,  982, 788,  984, 1660,  984, 794,  1872, 1664,  1872, 1664,  980, 794,  1872};  // RC5 8D6
uint16_t rawDataJoystickRightButtonUp[] = {946, 828,  950, 826,  1840, 824,  948, 824,  948, 1696,  978, 798,  1840, 1696,  1840, 1698,  948, 828,  1838};  // RC5 8D6

uint16_t rawDataJoystickEnterButtonDown[] = {940, 836,  1830, 832,  942, 834,  938, 832,  944, 1702,  936, 838,  942, 834,  938, 840,  1828, 1704,  1828, 1710,  942};  // RC5 F5
uint16_t rawDataJoystickEnterButtonUp[] = {950, 830,  1828, 838,  936, 834,  940, 828,  944, 1700,  942, 834,  940, 836,  942, 834,  1832, 1706,  1830, 1704,  942};  // RC5 F5

uint16_t rawDataJoystickUpButtonDown[] = {976, 800,  950, 826,  1856, 808,  964, 808,  948, 1694,  966, 810,  1858, 1676,  1818, 1720,  1818, 848,  966};  // RC5 8D4
uint16_t rawDataJoystickUpButtonUp[] = {976, 802,  974, 804,  1864, 800,  974, 796,  950, 1694,  976, 800,  1864, 1672,  1866, 1670,  1866, 800,  974};  // RC5 8D4

uint16_t rawDataJoystickLeftButtonDown[] = {938, 842,  932, 842,  1824, 840,  934, 836,  934, 1708,  936, 842,  1824, 1708,  1826, 1708,  1828, 1712,  936};  // RC5 8D5
uint16_t rawDataJoystickLeftButtonUp[] = {936, 844,  932, 842,  1824, 840,  960, 814,  932, 1706,  938, 842,  1822, 1710,  1828, 1710,  1852, 1686,  936};  // RC5 8D5

uint16_t rawDataBackButtonDown[] = {936, 840,  936, 840,  1826, 838,  936, 836,  936, 1708,  936, 842,  1826, 838,  936, 1708,  1826, 1710,  1828};  // RC5 8CA
uint16_t rawDataBackButtonUp[] = {936, 842,  936, 842,  1824, 838,  936, 836,  936, 1708,  936, 840,  1826, 838,  934, 1708,  1826, 1710,  1826};  // RC5 8CA

uint16_t rawDataExitButtonDown[] = {964, 818,  1822, 842,  958, 814,  932, 840,  930, 1708,  936, 842,  934, 846,  1846, 814,  934, 1706,  1826, 1712,  936};  // RC5 E5
uint16_t rawDataExitButtonUp[] = {936, 846,  1820, 840,  932, 844,  952, 816,  930, 1708,  962, 820,  932, 846,  1846, 816,  930, 1708,  1854, 1686,  936};  // RC5 E5

uint16_t rawDataMuteButtonDown[] = {936, 842,  934, 844,  1824, 840,  934, 838,  934, 1708,  936, 842,  1826, 840,  932, 1708,  936, 842,  1824, 1714,  936};  // RC5 8CD
uint16_t rawDataMuteButtonUp[] = {936, 842,  934, 842,  1824, 840,  934, 840,  928, 1710,  936, 842,  1824, 840,  932, 1708,  960, 818,  1824, 1712,  936};  // RC5 8CD

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

IRTVHitachi::IRTVHitachi(): IRTVBase( 4 ),
       mLoopCounter( 0 ), mLoopsOnYoutubeFromTVScratchCount( 92 ),
       mLoopsOnYoutubeFromTVInitialCount( 89 ), mStatusTopic( "HitachiStatus" )
{
}

void IRTVHitachi::prepareYoutubeFromTVScratchHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleYoutubeFromTVScratch, this );
}

void IRTVHitachi::prepareYoutubeFromTVInitialHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleYoutubeFromTVInitial, this );
}

int32_t IRTVHitachi::getLoopsOnYoutubeFromInitialCount()
{
  return mLoopsOnYoutubeFromTVInitialCount;
}

void IRTVHitachi::prepareMuteHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleMute, this );
}

void IRTVHitachi::prepareExitHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleExit, this );
}

void IRTVHitachi::prepareBackHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleBack, this );
}

void IRTVHitachi::prepareJoystickDownHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleJoystickDown, this );
}

void IRTVHitachi::prepareJoystickRightHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleJoystickRight, this );
}

void IRTVHitachi::prepareJoystickUpHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleJoystickUp, this );
}

void IRTVHitachi::prepareJoystickLeftHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleJoystickLeft, this );
}

void IRTVHitachi::prepareJoystickEnterHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleJoystickEnter, this );
}

void IRTVHitachi::preparePowerHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handlePower, this );
}

void IRTVHitachi::prepareSmartHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVHitachi::handleSmart, this );
}

void IRTVHitachi::handleMute()
{
//  Serial.println( "TV Mute button down" );
  mIrSend.sendRaw( rawDataMuteButtonDown, SIZEOF( rawDataMuteButtonDown ), mIRFrequency );
  delay( 100 );
//  Serial.println( "TV Mute button up" );
  mIrSend.sendRaw( rawDataMuteButtonUp, SIZEOF( rawDataMuteButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV Mute pressed" );
}

void IRTVHitachi::handleExit()
{
//  Serial.println( "TV Exit button down" );
  mIrSend.sendRaw( rawDataExitButtonDown, SIZEOF( rawDataExitButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataExitButtonUp, SIZEOF( rawDataExitButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV Exit pressed" );
}

void IRTVHitachi::handleBack()
{
//    Serial.println( "TV Back button down" );
  mIrSend.sendRaw( rawDataBackButtonDown, SIZEOF( rawDataBackButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataBackButtonUp, SIZEOF( rawDataBackButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV Back pressed" );
}

void IRTVHitachi::handleJoystickDown()
{
//    Serial.println( "TV JoystickDown button down" );
  mIrSend.sendRaw( rawDataJoystickDownButtonDown, SIZEOF( rawDataJoystickDownButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickDownButtonUp, SIZEOF( rawDataJoystickDownButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV JoystickDown pressed" );
}

void IRTVHitachi::handleJoystickRight()
{
//    Serial.println( "TV JoystickRight button down" );
  mIrSend.sendRaw( rawDataJoystickRightButtonDown, SIZEOF( rawDataJoystickRightButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickRightButtonUp, SIZEOF( rawDataJoystickRightButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV JoystickRight button" );
}

void IRTVHitachi::handleJoystickUp()
{
//    Serial.println( "TV JoystickUp button down" );
  mIrSend.sendRaw( rawDataJoystickUpButtonDown, SIZEOF( rawDataJoystickUpButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickUpButtonUp, SIZEOF( rawDataJoystickUpButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV JoystickUp button" );
}

void IRTVHitachi::handleJoystickLeft()
{
//    Serial.println( "TV JoystickLeft button down" );
  mIrSend.sendRaw( rawDataJoystickLeftButtonDown, SIZEOF( rawDataJoystickLeftButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickLeftButtonUp, SIZEOF( rawDataJoystickLeftButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV JoystickLeft button" );
}

void IRTVHitachi::handleJoystickEnter()
{
//    Serial.println( "TV JoystickEnter button down" );
  mIrSend.sendRaw( rawDataJoystickEnterButtonDown, SIZEOF( rawDataJoystickEnterButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataJoystickEnterButtonUp, SIZEOF( rawDataJoystickEnterButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV JoystickEnter button" );
}

void IRTVHitachi::handlePower()
{
//    Serial.println( "TV Power button down" );
  mIrSend.sendRaw( rawDataPowerOnButtonDown, SIZEOF( rawDataPowerOnButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataPowerOnButtonUp, SIZEOF( rawDataPowerOnButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV Power button" );
}

void IRTVHitachi::handleSmart()
{
//    Serial.println( "TV Smart button down" );
  mIrSend.sendRaw( rawDataSmartButtonDown, SIZEOF( rawDataSmartButtonDown ), mIRFrequency );
  delay( 100 );
  mIrSend.sendRaw( rawDataSmartButtonUp, SIZEOF( rawDataSmartButtonUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "TV Smart button" );
}

int32_t IRTVHitachi::getLoopsOneCommandCount()
{
  return 1;
}

void IRTVHitachi::handleYoutubeFromTVInitial()
{
//  Serial.print( __FUNCTION__ );Serial.println( " was called" );
  const int minDelay = 1000;
  mLoopCounter++;
//  Serial.print( "mLoopCounter=" );Serial.println( mLoopCounter );
  switch( mSequenceCounter )
  {
    case 0:
    {  
//      Serial.println( "TV Smart launching button down" );
      mIrSend.sendRaw( rawDataSmartButtonDown, SIZEOF( rawDataSmartButtonDown ), mIRFrequency );
      delay( 100 );
//      Serial.println( "TV Smart launching button up" );
      mIrSend.sendRaw( rawDataSmartButtonUp, SIZEOF( rawDataSmartButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV Smart pressed" );

      mSequenceCounter++;
      break;
    }
    case 1:
    {
//      Serial.println( "TV Wait after smart was launched" );
      mINet->publish( mStatusTopic.c_str(), "TV waits after smart was launched" );
      mSequenceCounter++;
      mDelayTimeSum = 0;
      break;
    }
    case 2:
    {
      delay( minDelay );
      mDelayTimeSum += minDelay;
      if( mDelayTimeSum > 30 * 1000 )
      {
        mDelayTimeSum = 0;
        mSequenceCounter++;
      }
      break;
    }
    case 3:
    {
//      Serial.println( "TV navigating to youtube begin" );
      mINet->publish( mStatusTopic.c_str(), "TV is navigating to youtube begin" );
      mSequenceCounter++;
      break;
    }
    case 4:
    case 6:
    case 8:
    case 10:
    {
//      Serial.println( "TV navigating down" );
      mIrSend.sendRaw( rawDataJoystickDownButtonDown, SIZEOF( rawDataJoystickDownButtonDown ), mIRFrequency );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickDownButtonUp, SIZEOF( rawDataJoystickDownButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV is navigating down" );
      mSequenceCounter++;
      mDelayTimeSum = 0;
      break;
    }
    case 5:
    case 7:
    case 9:
    case 11:
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
    case 12:
    case 14:
    case 16:
    {
//      Serial.println( "TV navigating right" );
      mIrSend.sendRaw( rawDataJoystickRightButtonDown, SIZEOF( rawDataJoystickRightButtonDown ), mIRFrequency );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickRightButtonUp, SIZEOF( rawDataJoystickRightButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV is navigating right" );
      mSequenceCounter++;
      mDelayTimeSum = 0;
      break;
    }
    case 13:
    case 15:
    case 17:
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
    case 18:
    {
//      Serial.println( "TV navigating to youtube finished" );
      mINet->publish( mStatusTopic.c_str(), "TV is navigating to youtube finished" );
      mSequenceCounter++;
      break;
    }
    case 19:
    {
//      Serial.println( "TV Joystick pressing on Youtube icon" );
      mIrSend.sendRaw( rawDataJoystickEnterButtonDown, SIZEOF( rawDataJoystickEnterButtonDown ), mIRFrequency );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickEnterButtonUp, SIZEOF( rawDataJoystickEnterButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV Joystick pressing on Youtube icon" );
      mSequenceCounter++;
      break;
    }
    case 20:
    {
//      Serial.println( "TV Youtube shoulbe launched" );
      mINet->publish( mStatusTopic.c_str(), "TV Youtube shoulbe launched" );
      mSequenceCounter++;
      break;
    }
    case 21:
    {
      mSequenceCounter = 0;
    }
  }
//  Serial.print( __FUNCTION__ );Serial.println( " leave" );
}

void IRTVHitachi::handleYoutubeFromTVScratch()
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
//      Serial.println( "TV Powering-on button down" );
      mIrSend.sendRaw( rawDataPowerOnButtonDown, SIZEOF( rawDataPowerOnButtonDown ), mIRFrequency );
      delay( 100 );
//      Serial.println( "TV Powering-on button up" );
      mIrSend.sendRaw( rawDataPowerOnButtonUp, SIZEOF( rawDataPowerOnButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV Power pressed" );

      mSequenceCounter++;

      break;
    }
    case 1:
    {
//      Serial.println( "TV Wait after TV was powered-on" );
      mINet->publish( mStatusTopic.c_str(), "TV Wait after TV was powered" );
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
//      Serial.println( "TV Smart launching button down" );
      mIrSend.sendRaw( rawDataSmartButtonDown, SIZEOF( rawDataSmartButtonDown ), mIRFrequency );
      delay( 100 );
//      Serial.println( "TV Smart launching button up" );
      mIrSend.sendRaw( rawDataSmartButtonUp, SIZEOF( rawDataSmartButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV Smart pressed" );

      mSequenceCounter++;
      break;
    }
    case 4:
    {
//      Serial.println( "TV Wait after smart was launched" );
      mINet->publish( mStatusTopic.c_str(), "TV Wait after smart was launched" );
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
//      Serial.println( "TV navigating to youtube begin" );
      mINet->publish( mStatusTopic.c_str(), "TV navigating to youtube begin" );
      mSequenceCounter++;
      break;
    }
    case 7:
    case 9:
    case 11:
    case 13:
    {
//      Serial.println( "TV navigating down" );
      mIrSend.sendRaw( rawDataJoystickDownButtonDown, SIZEOF( rawDataJoystickDownButtonDown ), mIRFrequency );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickDownButtonUp, SIZEOF( rawDataJoystickDownButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV navigating down" );
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
//      Serial.println( "TV navigating right" );
      mIrSend.sendRaw( rawDataJoystickRightButtonDown, SIZEOF( rawDataJoystickRightButtonDown ), mIRFrequency );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickRightButtonUp, SIZEOF( rawDataJoystickRightButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV navigating right" );
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
//      Serial.println( "TV navigating to youtube finished" );
      mINet->publish( mStatusTopic.c_str(), "TV navigating to youtube finished" );
      mSequenceCounter++;
      break;
    }
    case 22:
    {
//      Serial.println( "TV Joystick pressing on Youtube icon" );
      mIrSend.sendRaw( rawDataJoystickEnterButtonDown, SIZEOF( rawDataJoystickEnterButtonDown ), mIRFrequency );
      delay( 100 );
      mIrSend.sendRaw( rawDataJoystickEnterButtonUp, SIZEOF( rawDataJoystickEnterButtonUp ), mIRFrequency );
      mINet->publish( mStatusTopic.c_str(), "TV Joystick pressing on Youtube icon" );
      mSequenceCounter++;
      break;
    }
    case 23:
    {
//      Serial.println( "TV Youtube shoulbe launched" );
      mINet->publish( mStatusTopic.c_str(), "TV Youtube shoulbe launched" );
      mSequenceCounter++;
      break;
    }
    case 24:
    {
      mSequenceCounter = 0;
    }
  }
}

int32_t IRTVHitachi::getLoopsOnYoutubeFromScratchCount()
{
  return mLoopsOnYoutubeFromTVScratchCount;
}
