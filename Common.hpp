#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

#define IRTOPIC_FUNC_PREPARE(devtype, devmodel, devcommand, rawBytes, className)\
void prepare_##devtype##_##devmodel##_##devcommand()\
{\
  resetSequence();\
  (*mHandler) = std::bind( &className::handle_##devtype##_##devmodel##_##devcommand, this );\
}\
void handle_##devtype##_##devmodel##_##devcommand()\
{\
  /*Serial.println( "##devtype## ##devmodel## ##devcommand On" );*/\
  mIrSend.sendRaw( rawBytes, SIZEOF( rawBytes ), mIRFrequency );\
  mINet->publish( mStatusTopic.c_str(), ""#devtype"_"#devmodel"_"#devcommand"" );\
}
#define IRTOPIC_FUNC_PREPARE_GET(devtype, devmodel, devcommand) prepare_##devtype##_##devmodel##_##devcommand
#define IRTOPIC_STR(devtype, devmodel, devcommand) std::string mqtt_topic_##devtype##_##devmodel##_##devcommand = ""#devtype"_"#devmodel"_"#devcommand"";
#define IRTOPIC_STR_GET(dev_type, dev_model, dev_command) mqtt_topic_##dev_type##_##dev_model##_##dev_command

#define IRTOPIC_STR_AND_FUNC(devtype, devmodel, devcommand, rawBytes, className)\
IRTOPIC_STR(devtype, devmodel, devcommand)\
IRTOPIC_FUNC_PREPARE(devtype, devmodel, devcommand, rawBytes, className)

#endif
