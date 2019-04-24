#include "IRTVHitachi.h"

IRTVHitachi::IRTVHitachi(): IRTVBase( 4 ),
       mLoopCounter( 0 ), mLoopsOnYoutubeFromTVScratchCount( 92 ),
       mLoopsOnYoutubeFromTVInitialCount( 89 ), mStatusTopic( "HitachiStatus" )
{
}

bool IRTVHitachi::process( std::string topic )
{
  bool result = false;
  return result;
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
