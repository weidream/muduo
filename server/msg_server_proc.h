#ifndef _IM_SERVER_PROC_H_
#define _IM_SERVER_PROC_H_
#include "codec.h"
#include "dispatcher.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>

class ProtobufDispatcher;
class ProtobufCodec;
namespace msgserver {
typedef boost::shared_ptr<ProtobufDispatcher> ProtobufDispatcherPtr;
typedef boost::shared_ptr<ProtobufCodec> ProtobufCodecPtr;

class MsgServerProc : boost::noncopyable {
public:
  static MsgServerProc *instance();
  void onMessage(const muduo::net::TcpConnectionPtr &conn,
                 muduo::net::Buffer *buf, muduo::Timestamp receiveTime);
  ProtobufDispatcherPtr &getDispatcher() { return dispatcherptr_; }

  boost::shared_ptr<ProtobufCodec> getCodec() { return codecptr_; }

  void send(const muduo::net::TcpConnectionPtr &conn,
            const google::protobuf::Message &message) {
    codecptr_->send(conn, message);
  };

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
