#include "msg_server.h"
#include "msg_server_proc.h"
#include "stdio.h"
#include "user_manager.h"
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <muduo/base/Timestamp.h>

using namespace muduo;
using namespace muduo::net;

namespace msgserver {

__thread int t_loop_index; // for eventloop index

AtomicInt32 MsgServer::globalCount_;

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
  dispatcher->registerMessageCallback<IMMessage::IMMsgData>(
      boost::bind(&MsgServer::OnIMMsgData, this, _1, _2, _3));
}

void MsgServer::threadInit(EventLoop *loop) {
  // init the thread local data
  assert(LocalConnections_::pointer() == NULL);
  assert(LocalUserManager::pointer() == NULL);
  LocalConnections_::instance();
  LocalUserManager::instance();
  assert(LocalConnections_::pointer() != NULL);
  assert(LocalUserManager::pointer() != NULL);
  MutexLockGuard lock(mutex_);
  t_loop_index = globalCount_.incrementAndGet();
  loops_.insert(std::make_pair(t_loop_index, loop));
}

void MsgServer::start() {
  server_.setThreadInitCallback(boost::bind(&MsgServer::threadInit, this, _1));
  server_.start();
}
void MsgServer::runTimer() {
#if 0
  Timestamp now = Timestamp::now();
  for (auto it = conn_set_.begin(), end = conn_set_.end(); it != end;) {
    if ((*it)->checkConnectionExpired(now)) {
      it = conn_set_.erase(it);
    } else {
      ++it;
    }
  }
#endif
}

void MsgServer::onAnswer(const muduo::net::TcpConnectionPtr &,
                         const AnswerPtr &message, muduo::Timestamp) {}

void MsgServer::OnIMLoginReq(const muduo::net::TcpConnectionPtr &conn,
                             const IMLoginReqPtr &message,
                             muduo::Timestamp receiveTime) {

  std::string name = message->user_name();
  std::string client_version = message->client_version();
  uint32_t online_status = message->online_status();
  uint32_t client_type = message->client_type();
  LOG_INFO << name << " " << client_version << " "
           << "client_type";
  IMUserPtr pUser = LocalUserManager::instance().getUserByName(name);
  assert(!conn->getContext().empty());
  IMUserConnPtr pUserConn = boost::any_cast<IMUserConnPtr>(conn->getContext());
  pUserConn->setClienttype(client_type);
  pUserConn->setClientversion(client_version);
  pUserConn->setUserPtr(pUser);
  pUserConn->setOnlinestatus(online_status);
}

void MsgServer::OnIMMsgData(const muduo::net::TcpConnectionPtr &conn,
                            const IMMsgDataPtr &message,
                            muduo::Timestamp receiveTime) {}

void MsgServer::onConnection(const TcpConnectionPtr &conn) {
  LOG_INFO << conn->localAddress().toIpPort() << " -> "
           << conn->peerAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
  if (conn->connected()) {
    int32_t index = globalCount_.incrementAndGet();
    IMUserConnPtr pUserConn = boost::make_shared<IMUserConn>(index);
    conn->setContext(pUserConn);
    conn->setExpiredTime(addTime(Timestamp::now(), 8));

    // auto result =
    LocalConnections_::instance().insert(std::make_pair(index, conn));
    // assert(!result.second);
  } else {
    assert(!conn->getContext().empty());
    int32_t index = 0;
    {
      //??!!!!
      IMUserConnPtr pUserConn =
          boost::any_cast<IMUserConnPtr>(conn->getContext());
      index = pUserConn->getIdex();
    }
    assert(index != 0);
    LocalConnections_::instance().erase(index);
  }
}

} // namespace msgserver
