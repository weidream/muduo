#ifndef _IM_MSGSERVER_CLIENT_DB_H_
#define _IM_MSGSERVER_CLIENT_DB_H_
#include "msg_server_proc.h"
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
namespace msgserver {
class MsgServerDBClient : boost::noncopyable {
public:
  MsgServerDBClient(EventLoop *loop, const InetAddress &serverAddr);
  ~MsgServerDBClient(){};
  void send(const google::protobuf::Message &message) {
    MsgServerProc::instance()->send(connection_, message);
  }
  void connect() { client_.connect(); }

private:
  EventLoop *loop_;
  TcpClient client_;
  TcpConnectionPtr connection_;
};
}
#endif _IM_MSGSERVER_CLIENT_DB_H_
