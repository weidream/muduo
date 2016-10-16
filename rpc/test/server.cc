#include <rpc/RpcChannel.h>
#include <IMRpc.pb.h>
#include <rpc/test/echo.pb.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <rpc/RpcServer.h>

using namespace muduo;
using namespace muduo::net;
using namespace protobufrpc;
namespace echo {

class EchoServiceImpl : public EchoService {
public:
  virtual void Echo(::google::protobuf::RpcController *controller,
                    const ::echo::EchoRequest *request,
                    ::echo::EchoResponse *response,
                    ::google::protobuf::Closure *done) {
    LOG_INFO << "EchoServiceImpl::Solve";
    response->set_payload(request->payload());
    done->Run();
  }
};
}

int main(int argc, char const *argv[]) {
  int nThreads = argc > 1 ? atoi(argv[1]) : 1;
  LOG_INFO << "pid = " << getpid() << " threads = " << nThreads;
  EventLoop loop;
  int port = argc > 2 ? atoi(argv[2]) : 8888;
  InetAddress listenAddr(static_cast<uint16_t>(port));
  echo::EchoServiceImpl impl;
  RpcServer server(&loop, listenAddr);
  server.setThreadNum(nThreads);
  server.registerService(&impl);
  server.start();
  loop.loop();
  return 0;
}
