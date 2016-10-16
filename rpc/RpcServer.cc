#include "RpcServer.h"
#include <boost/bind.hpp>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>
#include <muduo/base/Logging.h>
#include <rpc/RpcChannel.h>

using namespace muduo;
using namespace muduo::net;
namespace protobufrpc {
RpcServer::RpcServer(EventLoop *loop, const InetAddress &listenAddr)
    : server_(loop, listenAddr, "RpcServer") {
  server_.setConnectionCallback(
      boost::bind(&RpcServer::onConnection, this, _1));
}
void RpcServer::registerService(::google::protobuf::Service *service) {
  const google::protobuf::ServiceDescriptor *desc = service->GetDescriptor();
  services_[desc->name()] = service;
}
void RpcServer::onConnection(const TcpConnectionPtr &conn) {
  if (conn->connected()) {
    RpcChannelPtr channel(new RpcChannel(conn));
    channel->setServices(&services_);
    conn->setMessageCallback(
        boost::bind(&RpcChannel::onMessage, get_pointer(channel), _1, _2, _3));
    conn->setContext(channel);
  } else {
    conn->setContext(RpcChannelPtr()); // reset the channel
    // FIXME:
  }
}
void RpcServer::start()
{
  LOG_INFO << "RpcServer::start";
  server_.start();
}

}
