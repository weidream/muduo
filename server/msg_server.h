#ifndef _IM_SERVER_MSGSERVER_H_
#define _IM_SERVER_MSGSERVER_H_

#include <BaseDefine.pb.h>
#include <Login.pb.h>
#include <Message.pb.h>
//#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <set>

namespace msgserver {
typedef boost::shared_ptr<IMLogin::IMLoginReq> LoginReqPtr;
typedef boost::shared_ptr<IMMessage::IMMsgData> IMMsgDataPtr;
class MsgServer : boost::noncopyable {

public:
  MsgServer(muduo::net::EventLoop *loop,
            const muduo::net::InetAddress &listenAddr);

private:
  void MsgServer::IMLoginReq(const muduo::net::TcpConnectionPtr &conn,
                             LoginReqPtr message, muduo::Timestamp receiveTime);
  void MsgServer::IMMsgData(const muduo::net::TcpConnectionPtr &conn,
                            IMMsgDataPtr message, muduo::Timestamp receiveTime);
  void onConnection(const muduo::net::TcpConnectionPtr &conn);
  void runTimer();
  muduo::MutexLock mutex_;
  muduo::net::TcpServer server_;
  std::set<muduo::net::TcpConnectionPtr> conn_set_;
};

} // namespace msgserver
#endif
