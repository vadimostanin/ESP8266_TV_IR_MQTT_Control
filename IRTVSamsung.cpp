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
  //Serial.print( "subscribe called\n");
  //Serial.printf( "subscribe %s topic", IRTOPIC_TVSAM_STR_GET(power).c_str());
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(power)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(power), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(volume_up)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(volume_up), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(volume_down)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(volume_down), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(volume_muteunmute)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(volume_muteunmute), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(channel_up)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(channel_up), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(channel_down)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(channel_down), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(back)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(back), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(home)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(home), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(playpause)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(playpause), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_up)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_up), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_down)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_down), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_left)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_left), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_right)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_right), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(joystick_enter)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(joystick_enter), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(numerical)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(numerical), this );
  mTopicListeners[IRTOPIC_TVSAM_STR_GET(colordots)] = std::bind(& IRTOPIC_TVSAM_FUNC_PREPARE_GET(colordots), this );

  static const auto emptyFunc = [](){};
  for( const auto & topicInfo : mTopicListeners )
  {
    mINet->subscribe( topicInfo.first, emptyFunc );
  }
}

bool IRTVSamsung::process( std::string topic )
{
  bool result = false;
  const auto foundListenerIter = mTopicListeners.find( topic );
  //Serial.printf( "Samsung::processed called\n" );
  if( foundListenerIter != std::end( mTopicListeners ) )
  {
    //Serial.print( "Samsung::processed Topic \""); Serial.print( topic.c_str() ); Serial.println( "\" processed" );
    foundListenerIter->second();
    result = true;
  }
  else
  {
    //Serial.print( "Samsung::processed Topic \""); Serial.print( topic.c_str() ); Serial.println( "\" not found" );
  }
  return result;
}
