#include "msg_server.h"
#include "msg_server_proc.h"
#include <muduo/base/Timestamp.h>

using namespace muduo;
using namespace muduo::net;

namespace msgserver {

MsgServer::MsgServer(EventLoop *loop, const InetAddress &listenAddr)
    : server_(loop, listenAddr, "msgServer") {
  server_.setMessageCallback(boost::bind(
      &MsgServerProc::onMessage, MsgServerProc::instance(), _1, _2, _3));
  server_.setConnectionCallback(
      boost::bind(&MsgServer::onConnection, this, _1));
  auto dispatcher = MsgServerProc::instance()->getDispatcher();
  dispatcher->registerMessageCallback<IMLogin::IMLoginReq>(
      boost::bind(&MsgServer::IMLoginReq, this, _1, _2, _3));
  dispatcher->registerMessageCallback<IMMessage::IMMsgData>(
      boost::bind(&MsgServer::IMLoginReq, this, _1, _2, _3));
}

void MsgServer::runTimer() {
  Timestamp now = Timestamp::now();
  for (auto it = conn_set_.begin(), end = conn_set_.end(); it != end;) {
    if ((*it)->checkConnectionExpired(now)) {
      it = conn_set_.erase(it);
    } else {
      ++it;
    }
  }
}

void MsgServer::IMLoginReq(const muduo::net::TcpConnectionPtr &conn,
                           LoginReqPtr message, muduo::Timestamp receiveTime) {

  std::string &name = message.user_name();
  std::string &client_version = message.client_version();
  uint32_t online_status = message.online_status();
  uint32_t client_type = message.client_type();
  IMUserPtr pUser = UserManager::instance()->getUserByName(name);
  try {
    UserConnPtr &old_user_conn =
        boost::any_cast<UserConnPtr>(conn->getContext());
  } catch (boost::bad_any_cast e) {
    // FIXME
    conn->setContext(boost::make_shared<UserConn>(client_version, pUser,
                                                  client_type, online_status));
  }

}

void MsgServer::IMMsgData(const muduo::net::TcpConnectionPtr &conn,
                          IMMsgDataPtr message, muduo::Timestamp receiveTime) {}

void MsgServer::onConnection(const TcpConnectionPtr &conn) {
  if (conn->connected()) {
    conn->setExpiredTime(addTime(Timestamp::now(), 8));
    conn_set_.insert(conn);
  } else {
    conn_set_.erase(conn);
  }
}

} // namespace msgserver
