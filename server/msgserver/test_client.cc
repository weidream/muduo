#include <IMBaseDefine.pb.h>
#include <IMLogin.pb.h>
#include <IMMessage.pb.h>
#include <boost/bind.hpp>
#include <codec/codec.h>
#include <codec/dispatcher.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/TcpClient.h>

#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace muduo;
using namespace muduo::net;

typedef boost::shared_ptr<IMLogin::IMLoginRes> IMLoginRspPtr;
typedef boost::shared_ptr<IMMessage::IMMsgData> IMMsgDataPtr;
bool register_success = false;
uint32_t message_id = 1;
google::protobuf::Message *messageToSend;

class MsgClient : boost::noncopyable {
public:
  MsgClient(EventLoop *loop, const InetAddress &serverAddr)
      : loop_(loop), client_(loop, serverAddr, "MsgClient"),
        dispatcher_(
            boost::bind(&MsgClient::onUnknownMessage, this, _1, _2, _3)),
        codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage, &dispatcher_,
                           _1, _2, _3)) {
    dispatcher_.registerMessageCallback<IMLogin::IMLoginRes>(
        boost::bind(&MsgClient::onIMLoginRes, this, _1, _2, _3));
    client_.setConnectionCallback(
        boost::bind(&MsgClient::onConnection, this, _1));
    client_.setMessageCallback(
        boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
  }

  void connect() { client_.connect(); }
  void write(google::protobuf::Message &msg) { codec_.send(connection_, msg); }
  void disconnect() { client_.disconnect(); }

private:
  void onConnection(const TcpConnectionPtr &conn) {
    LOG_INFO << conn->localAddress().toIpPort() << " -> "
             << conn->peerAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected()) {
      connection_ = conn;
      IMLogin::IMLoginReq req;
      req.set_user_name("weigd");
      req.set_password("test");
      req.set_online_status(IMBaseDefine::UserStatType::USER_STATUS_ONLINE);
      req.set_client_type(IMBaseDefine::ClientType::CLIENT_TYPE_WINDOWS);
      req.set_client_version("1.1");
      codec_.send(conn, req);
    } else {
      loop_->quit();
    }
  }

  void onUnknownMessage(const TcpConnectionPtr &, const MessagePtr &message,
                        Timestamp) {
    LOG_INFO << "onUnknownMessage: " << message->GetTypeName();
  }

  void onIMLoginRes(const muduo::net::TcpConnectionPtr &,
                    const IMLoginRspPtr &message, muduo::Timestamp) {
    register_success = true;
  }

  EventLoop *loop_;
  TcpClient client_;
  ProtobufDispatcher dispatcher_;
  ProtobufCodec codec_;
  TcpConnectionPtr connection_;
};

int main(int argc, char *argv[]) {
  LOG_INFO << "pid = " << getpid();

  EventLoopThread loopThread;
  uint16_t port = 8888;
  InetAddress serverAddr("127.0.0.1", port);

  MsgClient client(loopThread.startLoop(), serverAddr);
  client.connect();
  std::string line;
  while (std::getline(std::cin, line)) {
    if (register_success) {
      IMMessage::IMMsgData msgdata;
      msgdata.set_from_user_id(10000);
      msgdata.set_to_session_id(10001);
      msgdata.set_msg_id(message_id++);
      msgdata.set_create_time(static_cast<uint32_t>(time(NULL)));
      msgdata.set_msg_type(IMBaseDefine::MsgType::MSG_TYPE_SINGLE_TEXT);
      msgdata.set_msg_data(line);
      client.write(msgdata);
    }
  }
  client.disconnect();
  CurrentThread::sleepUsec(1000 * 1000);
  return 0;
}
