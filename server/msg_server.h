#ifndef _IM_SERVER_MSGSERVER_H_
#define _IM_SERVER_MSGSERVER_H_

#include <IMBaseDefine.pb.h>
#include <IMLogin.pb.h>
#include <IMMessage.pb.h>
#include <query.pb.h>
//#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

#include <muduo/base/Atomic.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/ThreadLocalSingleton.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

namespace msgserver {

typedef boost::shared_ptr<IMLogin::IMLoginReq> IMLoginReqPtr;
typedef boost::shared_ptr<IMMessage::IMMsgData> IMMsgDataPtr;
typedef boost::shared_ptr<muduo::Answer> AnswerPtr;
class UserManager;
class MsgServer : boost::noncopyable {

public:
  MsgServer(muduo::net::EventLoop *loop,
            const muduo::net::InetAddress &listenAddr);
  ~MsgServer() {}
  void start();
  void setThreadNum(int numThreads) { server_.setThreadNum(numThreads); }

private:
  void threadInit(muduo::net::EventLoop *loop);
  void OnIMLoginReq(const muduo::net::TcpConnectionPtr &conn,
                    const IMLoginReqPtr &message, muduo::Timestamp receiveTime);

  void OnIMMsgData(const muduo::net::TcpConnectionPtr &conn,
                   const IMMsgDataPtr &message, muduo::Timestamp receiveTime);
  void onAnswer(const muduo::net::TcpConnectionPtr &, const AnswerPtr &message,
                muduo::Timestamp);
  void onConnection(const muduo::net::TcpConnectionPtr &conn);
  void runTimer();

  typedef muduo::ThreadLocalSingleton<UserManager> LocalUserManager;
  typedef std::map<uint32_t /*globalCount_*/, muduo::net::TcpConnectionPtr>
      ConnectionList;

  typedef muduo::ThreadLocalSingleton<ConnectionList> LocalConnections_;

  muduo::MutexLock mutex_;
  muduo::net::TcpServer server_;
  std::map<uint32_t /*globalCount_*/, muduo::net::EventLoop *> loops_;
  static muduo::AtomicInt32 globalCount_; // connection and eventloop index
};

} // namespace msgserver
#endif
