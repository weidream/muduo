#include "msg_client_db.h"
#include "msg_server_proc.h"

namespace msgserver {

MsgServerDBClient::MsgServerDBClient(EventLoop *loop,
                                     const InetAddress &serverAddr)
    : loop_(loop), client_(loop, serverAddr, "MsgDbClient") {
  client_.setMessageCallback(boost::bind(
      &MsgServerProc::onMessage, MsgServerProc::instance(), _1, _2, _3));
  auto dispatcher = MsgServerProc::instance()->getDispatcher();
  dispatcher->registerMessageCallback<IMLogin::IMLoginRes>(
      boost::bind(&MsgServerDBClient::IMLoginRes, this, _1, _2, _3));
}

void MsgServerDBClient::IMLoginRes(const muduo::net::TcpConnectionPtr &conn,
                                   LoginReqPtr message,
                                   muduo::Timestamp receiveTime) {}
}
