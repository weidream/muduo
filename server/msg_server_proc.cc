#include "msg_server_proc.h"
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <muduo/base/Timestamp.h>
namespace msgserver {
MsgServerProc::MsgServerProc()
    : dispatcherptr_(boost::make_shared<ProtobufDispatcher>(
          boost::bind(&MsgServerProc::onUnKnowMessage, this, _1, _2, _3))),
      codecptr_(boost::make_shared<ProtobufCodec>(
          boost::bind(&ProtobufDispatcher::onProtobufMessage,
                      dispatcherptr_.get(), _1, _2, _3))) {}

MsgServerProc *MsgServerProc::instance() {
  static MsgServerProc T;
  return &T;
}

void MsgServerProc::onMessage(const muduo::net::TcpConnectionPtr &conn,
                              muduo::net::Buffer *buf,
                              muduo::Timestamp receiveTime) {
  conn->setExpiredTime(addTime(muduo::Timestamp::now(), 30));
  codecptr_->onMessage(conn, buf, receiveTime);
}

void MsgServerProc::onUnKnowMessage(const muduo::net::TcpConnectionPtr &conn,
                                    const MessagePtr &message,
                                    muduo::Timestamp) {}

} // namespace msgserver
