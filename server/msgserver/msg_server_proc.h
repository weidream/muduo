#ifndef _IM_SERVER_PROC_H_
#define _IM_SERVER_PROC_H_
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <codec/codec.h>
#include <codec/dispatcher.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>

namespace msgserver {

class MsgServerProc : boost::noncopyable {
public:
  static MsgServerProc *instance();
  void onMessage(const muduo::net::TcpConnectionPtr &conn,
                 muduo::net::Buffer *buf, muduo::Timestamp receiveTime);
  ProtobufDispatcherPtr &getDispatcher() { return dispatcherptr_; }

  boost::shared_ptr<ProtobufCodec> getCodec() { return codecptr_; }

  void send(const muduo::net::TcpConnectionPtr &conn,
            const MessagePtr &message) {
    codecptr_->send(conn, *message);
  }

private:
  MsgServerProc();
  ~MsgServerProc() {}
  void onUnKnowMessage(const muduo::net::TcpConnectionPtr &conn,
                       const MessagePtr &message, muduo::Timestamp);
  ProtobufDispatcherPtr dispatcherptr_;
  ProtobufCodecPtr codecptr_;
};

} // namespace msgserver

#endif //_IM_SERVER_PROC_H
