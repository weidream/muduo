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

class IMUser : boost::noncopyable {
public:
  IMUser(const std::string &);
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

class IMUserConn : boost::noncopyable {
public:
  IMUserConn(int32_t index)
      : index_(index), client_version_("windos-pc1.1"), client_type_(1),
        online_status_(1), login_time_(muduo::Timestamp::now()) {}
  ~IMUserConn() {}
  void setClientversion(const std::string &rhs) { client_version_ = rhs; }
  void setUserPtr(const IMUserPtr &rhs) { user_ptr_ = rhs; }
  void setClienttype(const uint32_t type) { client_type_ = type; }
  void setOnlinestatus(const uint32_t status) { online_status_ = status; }
  int32_t getIdex() { return index_; }

private:
  int32_t index_; // the index of usermanager map
  std::string client_version_;
  IMUserPtr user_ptr_;
  uint32_t client_type_;
  uint32_t online_status_;
  muduo::Timestamp login_time_;
};

typedef boost::shared_ptr<IMUserConn> IMUserConnPtr;
}

#endif
