#ifndef __IRTVHITACHI_H__
#define __IRTVHITACHI_H__

#include "IRTVBase.h"
#include "Common.hpp"

namespace
{
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
}
#define IRTOPIC_TVHIT_STR_GET(dev_command) IRTOPIC_STR_GET(tv, hitachi, dev_command)
#define IRTOPIC_TVHIT_FUNC_PREPARE_GET(devcommand) IRTVSamsung::IRTOPIC_FUNC_PREPARE_GET(tv, hitachi, devcommand)
#define IRTOPIC_TVHIT_STR_AND_FUNC(devcommand, rawBytes) IRTOPIC_STR_AND_FUNC(tv, hitachi, devcommand, rawBytes, IRTVHitachi)

class IRTVHitachi : public IRTVBase
{
public:
  IRTVHitachi();

  void prepareMuteHandler();
  void prepareExitHandler();
  void prepareBackHandler();
  void prepareJoystickDownHandler();
  void prepareJoystickRightHandler();
  void prepareJoystickUpHandler();
  void prepareJoystickLeftHandler();
  void prepareJoystickEnterHandler();
  void preparePowerHandler();
  void prepareSmartHandler();
  void prepareYoutubeFromTVScratchHandler();
  void prepareYoutubeFromTVInitialHandler();
  int32_t getLoopsOnYoutubeFromScratchCount();
  int32_t getLoopsOnYoutubeFromInitialCount();
  int32_t getLoopsOneCommandCount();

  bool process( std::string topic );
private:
  void handleMute();
  void handleExit();
  void handleBack();
  void handleJoystickDown();
  void handleJoystickRight();
  void handleJoystickUp();
  void handleJoystickLeft();
  void handleJoystickEnter();
  void handlePower();
  void handleSmart();
  void handleYoutubeFromTVScratch();
  void handleYoutubeFromTVInitial();

  int32_t mDelayTimeSum;
  int32_t mLoopCounter;

  int32_t mLoopsOnYoutubeFromTVScratchCount;
  int32_t mLoopsOnYoutubeFromTVInitialCount;

  std::string mStatusTopic;
};
#endif
