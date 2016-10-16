#include <assert.h>
#include <boost/bind.hpp>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <server/base/timingWheel.h>
#include <stdio.h>
using namespace muduo;
using namespace muduo::net;
typedef typename timingWheel::EntryPtr EntryPtr;
typedef typename timingWheel::WeakEntryPtr WeakEntryPtr;
typedef typename timingWheel::Bucket Bucket;
typedef boost::weak_ptr<TcpConnection> wkTcpConnectionPtr;
class myEchoServer
{
public:
  myEchoServer(EventLoop *loop, const InetAddress &listenAddr, int idleSeconds)
      : server_(loop, listenAddr, "myEchoServer"), tw_(idleSeconds)
  {
    server_.setConnectionCallback(
        boost::bind(&myEchoServer::onConnection, this, _1));
    server_.setMessageCallback(
        boost::bind(&myEchoServer::onMessage, this, _1, _2, _3));
    loop->runEvery(1.0, boost::bind(&myEchoServer::onTimer, this));
    // tw_.resize(idleSeconds);
    dumpConnectionBuckets();
  }

  void start() { server_.start(); }
  void closeConn(const wkTcpConnectionPtr &conn)
  {
    LOG_INFO << "closeConn";
    TcpConnectionPtr p(conn.lock());
    if (p)
      p->shutdown();
  }
  void onConnection(const TcpConnectionPtr &conn)
  {
    LOG_INFO << "myEchoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected())
    {
      WeakEntryPtr weakEntry =
          tw_.insert(boost::bind(&myEchoServer::closeConn, this, conn), 6);
      dumpConnectionBuckets();
      conn->setContext(weakEntry);
    }
    else
    {
      assert(!conn->getContext().empty());
      timingWheel::WeakEntryPtr weakEntry(boost::any_cast<timingWheel::WeakEntryPtr>(conn->getContext()));
      LOG_DEBUG << "Entry use_count = " << weakEntry.use_count();
    }
  }

  void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
  {
    LOG_DEBUG << "onMessage in";
    string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes at "
             << time.toString();
    conn->send(msg);
    LOG_DEBUG << "onMessage out";
    assert(!conn->getContext().empty());
    WeakEntryPtr weakEntry(boost::any_cast<WeakEntryPtr>(conn->getContext()));
    EntryPtr entry(weakEntry.lock());
    LOG_DEBUG << "Entry use_count = " << entry.use_count();
    if (entry)
    {
      printf("Entry use_count = %ld\n" ,entry.use_count());
      tw_.insert(entry);
      dumpConnectionBuckets();
    }else{
       printf("error null\n");
    }
  }

  void onTimer() { 
       LOG_INFO << "onTimer";
    tw_.on_timer(); }

  void dumpConnectionBuckets() const
  {

    LOG_INFO << "size = " << tw_.list_.size();
    int idx = 0;
    for (auto bucketI = tw_.list_.begin(); bucketI != tw_.list_.end();
         ++bucketI, ++idx) {
      const Bucket &bucket = *bucketI;
      printf("[%d] len = %zd : ", idx, bucket.size());
      #if 0
      for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        bool connectionDead = (*it)->weakConn_.expired();
        printf("%p(%ld)%s, ", get_pointer(*it), it->use_count(),
               connectionDead ? " DEAD" : "");
      }
      #endif
      puts("");
    }

  }

private:
  muduo::net::TcpServer server_;
  timingWheel tw_;
};

int main(int argc, char *argv[])
{

  EventLoop loop;
  InetAddress listenAddr(2007);
  int idleSeconds = 10;
  if (argc > 1)
  {
    idleSeconds = atoi(argv[1]);
  }
  LOG_INFO << "pid = " << getpid() << ", idle seconds = " << idleSeconds;
  myEchoServer server(&loop, listenAddr, idleSeconds);
  server.start();
  loop.loop();
}
