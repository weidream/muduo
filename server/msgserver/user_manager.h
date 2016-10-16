#ifndef _IM_SERVER_USERMANAGER_H_
#define _IM_SERVER_USERMANAGER_H_

#include "user.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <map>
#include <string>

namespace msgserver
{
typedef std::map<std::string, IMUserWeakPtr> UserMap;

class UserManager : boost::noncopyable
{
public:
  // static UserManager *instance();
  // IMUserWeakPtr getUserById(){};
  IMUserPtr getUserByName(const std::string &);

private:
  UserMap usermap_;
};
}
#endif
