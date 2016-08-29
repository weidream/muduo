#include "msg_server.h"
#include "msg_server_proc.h"
#include "user_manager.h"
#include <boost/shared_ptr.hpp>

using namespace msgserver;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  msgserver::MsgServerProc::instance();
  msgserver::UserManager::instance();

  muduo::net::EventLoop loop;

  loop.loop();

  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
