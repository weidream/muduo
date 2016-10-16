#ifndef _MUDUO_RPC_RPCSERVER_H
#define _MUDUO_RPC_RPCSERVER_H

#include <muduo/net/TcpServer.h>

namespace google {
namespace protobuf {

class Service;

} // namespace protobuf
}

namespace protobufrpc {
class RpcServer {
public:
  RpcServer(muduo::net::EventLoop *loop,
            const muduo::net::InetAddress &listenAddr);

  void setThreadNum(int numThreads) { server_.setThreadNum(numThreads); }

  void registerService(::google::protobuf::Service *);
  void start();

private:
  void onConnection(const muduo::net::TcpConnectionPtr &conn);
  muduo::net::TcpServer server_;
  std::map<std::string, ::google::protobuf::Service *> services_;
};
}

#endif
