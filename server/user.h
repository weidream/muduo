#ifndef _IM_SERVER_USER_H_
#define _IM_SERVER_USER_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <muduo/base/Timestamp.h>
#include <muduo/net/TcpServer.h>

#include <map>
#include <set>
#include <string>
namespace msgserver {

typedef class IMUser : boost::noncopyable {
  IMUser(const std::string name &);
  ~IMUser();

private:
  uint32_t uid_;
  std::string user_name_;
  muduo::Timestamp loginTime_;
  std::string clientVersion_;
  int clientType_;

  std::map<uint32_t, muduo::net::TcpConnectionPtr> unvalidCon_;

  // std::set<muduo::net::TcpConnectionPtr>
};
typedef boost::weak_ptr<IMUser> IMUserWeakPtr;
typedef boost::shared_ptr<IMUser> IMUserPtr;

class UserConn {
public:
  UserConn(const std::string &version, IMUserPtr &user, uint32_t client_type,
           uint32_t on_line_status)
      : login_time_(muduo::Timestamp::now()), client_version_(version),
        client_type_(client_type), user_ptr_(user),
        online_status_(on_line_status) {}

private:
  std::string client_version_;
  uint32_t client_type_;
  uint32_t online_status_;
  muduo::Timestamp login_time_;
  IMUserPtr user_ptr_;
};

typedef boost::shared_ptr<UserConn> UserConnPtr;
}

#endif
