#include "IRTVBase.h"

IRTVBase::IRTVBase( int32_t irPin ): mIrLed( irPin ), mIrSend( mIrLed ), 
                                     mIRFrequency( 38 * 1000 ), mSequenceCounter( 0 )
{
  ;
}

void IRTVBase::init()
{
  mIrSend.begin();
}

void IRTVBase::resetSequence()
{
  mSequenceCounter = 0;
}

void IRTVBase::setINet( std::shared_ptr<ISubPub> iNet )
{
  mINet = std::move(iNet);
}

void IRTVBase::setChangableHandler( std::shared_ptr<std::function<void()>> handler )
{
  mHandler = handler;
}
