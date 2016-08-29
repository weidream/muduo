#ifndef _IM_SERVER_MSGSERVER_H_
#define _IM_SERVER_MSGSERVER_H_

#include <IMBaseDefine.pb.h>
#include <IMLogin.pb.h>
#include <IMMessage.pb.h>
#include <query.pb.h>
//#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <set>

namespace msgserver {

typedef boost::shared_ptr<IMLogin::IMLoginReq> IMLoginReqPtr;
typedef boost::shared_ptr<IMMessage::IMMsgData> IMMsgDataPtr;
typedef boost::shared_ptr<muduo::Answer> AnswerPtr;
class MsgServer : boost::noncopyable {

public:
  MsgServer(muduo::net::EventLoop *loop,
            const muduo::net::InetAddress &listenAddr);

private:
  void OnIMLoginReq(const muduo::net::TcpConnectionPtr &conn,
                    IMLoginReqPtr &message, muduo::Timestamp receiveTime);

  void OnIMMsgData(const muduo::net::TcpConnectionPtr &conn,
                   IMMsgDataPtr &message, muduo::Timestamp receiveTime);
  void onAnswer(const muduo::net::TcpConnectionPtr &, const AnswerPtr &message,
                muduo::Timestamp);
  void onConnection(const muduo::net::TcpConnectionPtr &conn);
  void runTimer();
  muduo::MutexLock mutex_;
  muduo::net::TcpServer server_;
  std::set<muduo::net::TcpConnectionPtr> conn_set_;
};

} // namespace msgserver
#endif
