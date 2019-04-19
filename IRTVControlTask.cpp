#include "IRTVControlTask.h"

IRTVControlTask::IRTVControlTask()
{
  mHandler = std::make_shared<std::function<void()>>();
  (*mHandler) = std::bind( &IRTVControlTask::emptyHandler, this );
}

void IRTVControlTask::init()
{
  mIrHitachi.init();
  mIrSamsung.init();

  mIrHitachi.setChangableHandler( mHandler );
  mIrSamsung.setChangableHandler( mHandler );
}

void IRTVControlTask::loopFunc()
{
  (*mHandler)();
}

std::function<void()> IRTVControlTask::getLoop()
{
  const auto func = [this](){ loopFunc(); };
  return std::bind( func );
}

void IRTVControlTask::setINet( std::shared_ptr<ISubPub> iNet )
{
  mIrHitachi.setINet( iNet );
  mIrSamsung.setINet( iNet );
}

void IRTVControlTask::emptyHandler()
{
  Serial.print( __FUNCTION__ );Serial.println( " was called" );
}

IRTVHitachi & IRTVControlTask::getHitachi()
{
  return mIrHitachi;
}

IRTVSamsung & IRTVControlTask::getSamsung()
{
  return mIrSamsung;
}

