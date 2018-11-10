#ifndef _ISUBPUB_H__
#define _ISUBPUB_H__
#include <string>
#include <functional>

class ISubPub
{
public:
  virtual void subscribe( const std::string & topic, const std::function<void()> & callback ) = 0;
  virtual void publish( const std::string & topic, const std::string & message ) = 0;
};

#endif
