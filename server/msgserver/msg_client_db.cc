#include "msg_client_db.h"
#include "msg_server_proc.h"
#include <muduo/base/Logging.h>
namespace msgserver {
using namespace muduo;
using namespace muduo::net;

MsgServerDBClient::MsgServerDBClient(EventLoop *loop,
                                     const InetAddress &serverAddr)
    : loop_(loop), client_(loop, serverAddr, "MsgDbClient") {

  client_.setConnectionCallback(
      boost::bind(&MsgServerDBClient::onConnection, this, _1));
  client_.setMessageCallback(boost::bind(
      &MsgServerProc::onMessage, MsgServerProc::instance(), _1, _2, _3));
  auto dispatcher = MsgServerProc::instance()->getDispatcher();
  dispatcher->registerMessageCallback<IMLogin::IMLoginRes>(
      boost::bind(&MsgServerDBClient::onIMLoginRes, this, _1, _2, _3));
}

void MsgServerDBClient::onConnection(const TcpConnectionPtr &conn) {

  LOG_INFO << conn->localAddress().toIpPort() << " -> "
           << conn->peerAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
  if (conn->connected()) {
    connection_ = conn;
  } else {
    // fix me
    connection_.reset();
  }
}

void MsgServerDBClient::send(const MessagePtr &message) {
  EventLoop::Functor f = boost::bind(
      &MsgServerProc::send, MsgServerProc::instance(), connection_, message);
  loop_->queueInLoop(f);
}

void MsgServerDBClient::onIMLoginRes(const muduo::net::TcpConnectionPtr &conn,
                                     const LoginResPtr &message,
                                     muduo::Timestamp receiveTime) {}
}
