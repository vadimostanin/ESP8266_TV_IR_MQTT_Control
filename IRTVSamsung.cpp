#include "IRTVSamsung.h"

uint16_t rawDataSamsungPowerOn[] = {4536, 4440,  620, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  616, 512,  616, 510,  618, 510,  618, 1638,  620, 1638,  618, 1638,  618, 510,  618, 512,  616, 510,  616, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  620, 1638,  618, 510,  616, 510,  616, 1640,  618, 1638,  618, 510,  616, 512,  616, 512,  618, 45958,  4530, 4448,  618, 1640,  618, 1638,  618, 1638,  620, 510,  616, 512,  616, 510,  616, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 510,  618, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1640,  618, 1638,  618, 1638,  618, 510,  618, 512,  616, 1638,  618, 1638,  620, 510,  624, 504,  618, 510,  618};  // SAMSUNG E0E06798
uint16_t rawDataSamsungVolumeUp[] = {};
uint16_t rawDataSamsungVolumeDown[] = {};
uint16_t rawDataSamsungVolumeMuteUnmute[] = {};
uint16_t rawDataSamsungChannelUp[] = {};
uint16_t rawDataSamsungChannelDown[] = {};
uint16_t rawDataSamsungBack[] = {};
uint16_t rawDataSamsungHome[] = {};
uint16_t rawDataSamsungPlayPause[] = {};
uint16_t rawDataSamsungJoystickUp[] = {};
uint16_t rawDataSamsungJoystickDown[] = {};
uint16_t rawDataSamsungJoystickLeft[] = {};
uint16_t rawDataSamsungJoystickRight[] = {};
uint16_t rawDataSamsungJoystickEnter[] = {};
uint16_t rawDataSamsungNumerical[] = {};
uint16_t rawDataSamsungColorDots[] = {};

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
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungPower, this );
}

void IRTVSamsung::handleTVSamsungPower()
{
  Serial.println( "TV Samsung Power On" );
  mIrSend.sendRaw( rawDataSamsungPowerOn, SIZEOF( rawDataSamsungPowerOn ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "PoweredOn pressed" );
}

void IRTVSamsung::prepareSamsungVolumeUpHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungVolumeUp, this );
}

void IRTVSamsung::handleTVSamsungVolumeUp()
{
  Serial.println( "Volume Up" );
  mIrSend.sendRaw( rawDataSamsungVolumeUp, SIZEOF( rawDataSamsungVolumeUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "VolumeUp pressed" );
}

void IRTVSamsung::prepareSamsungVolumeDownHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungVolumeDown, this );
}

void IRTVSamsung::handleTVSamsungVolumeDown()
{
  Serial.println( "Volume Down" );
  mIrSend.sendRaw( rawDataSamsungVolumeDown, SIZEOF( rawDataSamsungVolumeDown ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "VolumeDown pressed" );
}

void IRTVSamsung::prepareSamsungVolumeMuteUnmuteHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungVolumeMuteUnmute, this );
}

void IRTVSamsung::handleTVSamsungVolumeMuteUnmute()
{
  Serial.println( "Volume Mute/Unmute" );
  mIrSend.sendRaw( rawDataSamsungVolumeMuteUnmute, SIZEOF( rawDataSamsungVolumeMuteUnmute ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "Volume Mute/Unmute pressed" );
}

void IRTVSamsung::prepareSamsungChannelUpHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungChannelUp, this );
}

void IRTVSamsung::handleTVSamsungChannelUp()
{
  Serial.println( "Channel Up" );
  mIrSend.sendRaw( rawDataSamsungChannelUp, SIZEOF( rawDataSamsungChannelUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "ChannelUp pressed" );
}

void IRTVSamsung::prepareSamsungChannelDownHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungChannelDown, this );
}

void IRTVSamsung::handleTVSamsungChannelDown()
{
  Serial.println( "Channel Down" );
  mIrSend.sendRaw( rawDataSamsungChannelDown, SIZEOF( rawDataSamsungChannelDown ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "ChannelDown pressed" );
}

void IRTVSamsung::prepareSamsungJoystickUpHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungJoystickUp, this );
}

void IRTVSamsung::handleTVSamsungJoystickUp()
{
  Serial.println( "Joystick Up" );
  mIrSend.sendRaw( rawDataSamsungJoystickUp, SIZEOF( rawDataSamsungJoystickUp ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "JoystickUp pressed" );
}

void IRTVSamsung::prepareSamsungJoystickDownHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungJoystickDown, this );
}

void IRTVSamsung::handleTVSamsungJoystickDown()
{
  Serial.println( "Joystick Down" );
  mIrSend.sendRaw( rawDataSamsungJoystickDown, SIZEOF( rawDataSamsungJoystickDown ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "JoystickDown pressed" );
}

void IRTVSamsung::prepareSamsungJoystickLeftHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungJoystickLeft, this );
}

void IRTVSamsung::handleTVSamsungJoystickLeft()
{
  Serial.println( "JoystickLeft" );
  mIrSend.sendRaw( rawDataSamsungJoystickLeft, SIZEOF( rawDataSamsungJoystickLeft ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "JoystickLeft pressed" );
}

void IRTVSamsung::prepareSamsungJoystickRightHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungJoystickRight, this );
}

void IRTVSamsung::handleTVSamsungJoystickRight()
{
  Serial.println( "JoystickRight" );
  mIrSend.sendRaw( rawDataSamsungJoystickRight, SIZEOF( rawDataSamsungJoystickRight ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "JoystickRight pressed" );
}

void IRTVSamsung::prepareSamsungJoystickEnterHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungJoystickEnter, this );
}

void IRTVSamsung::handleTVSamsungJoystickEnter()
{
  mIrSend.sendRaw( rawDataSamsungJoystickEnter, SIZEOF( rawDataSamsungJoystickEnter ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "JoystickEnter pressed" );
}

void IRTVSamsung::prepareSamsungNumericalHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungNumerical, this );
}

void IRTVSamsung::handleTVSamsungNumerical()
{
  Serial.println( "Numerical" );
  mIrSend.sendRaw( rawDataSamsungNumerical, SIZEOF( rawDataSamsungNumerical ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "Numerical pressed" );
}

void IRTVSamsung::prepareSamsungColorDotsHandler()
{
  resetSequence();
  (*mHandler) = std::bind( &IRTVSamsung::handleTVSamsungColorDots, this );
}

void IRTVSamsung::handleTVSamsungColorDots()
{
  Serial.println( "ColorDots pressed" );
  mIrSend.sendRaw( rawDataSamsungColorDots, SIZEOF( rawDataSamsungColorDots ), mIRFrequency );
  mINet->publish( mStatusTopic.c_str(), "ColorDots pressed" );
}

