#ifndef _IM_MSGSERVER_CLIENT_DB_H_
#define _IM_MSGSERVER_CLIENT_DB_H_

#include "msg_server.h"
#include <codec/codec.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>

namespace msgserver {
typedef boost::shared_ptr<IMLogin::IMLoginRes> LoginResPtr;

class MsgServerDBClient : boost::noncopyable {
public:
  MsgServerDBClient(muduo::net::EventLoop *loop,
                    const muduo::net::InetAddress &serverAddr);
  ~MsgServerDBClient(){};
  void connect() { client_.connect(); }
  void send(const MessagePtr &message);

private:
  void onConnection(const muduo::net::TcpConnectionPtr &conn);
  void distributeMessage(const MessagePtr &message);
  void onIMLoginRes(const muduo::net::TcpConnectionPtr &conn,
                    const LoginResPtr &message, muduo::Timestamp receiveTime);

  muduo::net::EventLoop *loop_;
  muduo::net::TcpClient client_;
  muduo::net::TcpConnectionPtr connection_;
};
} // namespace msgserver
#endif //_IM_MSGSERVER_CLIENT_DB_H_
