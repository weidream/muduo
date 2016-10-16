#include "msg_client_db.h"
#include "msg_server.h"
#include "msg_server_proc.h"
#include "user_manager.h"
#include <boost/shared_ptr.hpp>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoopThread.h>

using namespace msgserver;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[]) {
  LOG_INFO << "pid = " << getpid();
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  msgserver::MsgServerProc::instance();
  // start message server

  EventLoopThread loopThread;
  uint16_t port_db = 8889;
  InetAddress dbAddr("127.0.0.1", port_db);
  MsgServerDBClient dbclient(loopThread.startLoop(), dbAddr);
  dbclient.connect();

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
