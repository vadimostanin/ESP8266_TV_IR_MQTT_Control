#include "IRTVSamsung.h"

IRTVSamsung::IRTVSamsung(): IRTVBase( 4 ), mStatusTopic( "SamsungStatus" )
{
  ;
}

int32_t IRTVSamsung::getLoopsOneCommandCount()
{
  return 1;
}

void IRTVSamsung::subscribe()
{
  Serial.print( "subscribe called\n");
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(power)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(power), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(volume_up)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(volume_up), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(volume_down)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(volume_down), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(volume_muteunmute)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(volume_muteunmute), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(channel_up)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(channel_up), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(channel_down)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(channel_down), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_up)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_up), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_down)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_down), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_left)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_left), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_right)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_right), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_enter)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_enter), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(numerical)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(numerical), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(colordots)] = std::bind(&IRTVSamsung::IRTOPIC_TVSAM_FUNC_PREPARE_GET(colordots), this );
}

bool IRTVSamsung::process( std::string topic )
{
  bool result = false;
  const auto foundListenerIter = mTopicListeners.find( topic );
  if( foundListenerIter != std::end( mTopicListeners ) )
  {
    foundListenerIter->second();
    result = true;
  }
  else
  {
    Serial.print( "Topic \""); Serial.print( topic.c_str() ); Serial.println( "\" not found" );
  }
  return result;
}
