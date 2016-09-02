#include "msg_server.h"
#include "msg_server_proc.h"
#include "user_manager.h"
#include <boost/shared_ptr.hpp>
#include <muduo/base/Logging.h>

using namespace msgserver;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[]) {
  LOG_INFO << "pid = " << getpid();
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  msgserver::MsgServerProc::instance();

  // start message server
  muduo::net::EventLoop loop;
  uint16_t port = 8888;
  InetAddress serverAddr(port);
  MsgServer server(&loop, serverAddr);
  server.setThreadNum(5);
  server.start();
  loop.loop();
  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
