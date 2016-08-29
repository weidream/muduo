#include "msg_server.h"
#include "msg_server_proc.h"
#include "user_manager.h"
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
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
  auto func = boost::bind(&MsgServer::onAnswer, this, _1, _2, _3);
  dispatcher->registerMessageCallback<muduo::Answer>(func);

  dispatcher->registerMessageCallback<IMLogin::IMLoginReq>(
      boost::bind(&MsgServer::OnIMLoginReq, this, _1, _2, _3));
#if 0
  dispatcher->registerMessageCallback<IMMessage::IMMsgData>(
      boost::bind(&MsgServer::OnIMMsgData, this, _1, _2, _3));
#endif
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
void MsgServer::onAnswer(const muduo::net::TcpConnectionPtr &,
                         const AnswerPtr &message, muduo::Timestamp) {}
void MsgServer::OnIMLoginReq(const muduo::net::TcpConnectionPtr &conn,
                             IMLoginReqPtr &message,
                             muduo::Timestamp receiveTime) {
#if 0
  std::string name = message->user_name();
  std::string client_version = message->client_version();
  uint32_t online_status = message->online_status();
  uint32_t client_type = message->client_type();
  IMUserPtr pUser = UserManager::instance()->getUserByName(name);
  try {
    boost::any_cast<UserConnPtr>(conn->getContext());
  } catch (boost::bad_any_cast e) {
    // FIXME
    conn->setContext(boost::make_shared<UserConn>(client_version, pUser,
                                                  client_type, online_status));
  }
#endif
}

void MsgServer::OnIMMsgData(const muduo::net::TcpConnectionPtr &conn,
                            IMMsgDataPtr &message,
                            muduo::Timestamp receiveTime) {}

void MsgServer::onConnection(const TcpConnectionPtr &conn) {
  if (conn->connected()) {
    conn->setExpiredTime(addTime(Timestamp::now(), 8));
    conn_set_.insert(conn);
  } else {
    conn_set_.erase(conn);
  }
}

} // namespace msgserver
