#ifndef _MUDUO_SERVER_DBSERVER_CACHEPOOL_H
#define _MUDUO_SERVER_DBSERVER_CACHEPOOL_H

#include <boost/noncopyable.hpp>
#include <list>
#include <mysql.h>
#include <string>

//#include <map>
#include <memory>
#include <muduo/base/Condition.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/InetAddress.h>
#include <vector>

//#include <muduo/base/Logging.h>
class CacheConn;
class CacheConnGuard;

using std::string;
using muduo::Timestamp;
using muduo::MutexLock;

typedef std::shared_ptr<CacheConn> CacheConnPtr;
typedef std::unique_ptr<CacheConnGuard> CacheConnGuardPtr;
class CachePool : boost::noncopyable
{
public:
    CachePool(const string ip,int port,int max_con){};
    ~CachePool(){};

private:
    string ip_;
    int port;
    int max_con_;
    MutexLock mutex_;
    Condition notEmpty_;
};

class CacheConn : boost::noncopyable
{
  public:
  private:
};
class CacheConnGuard : boost::noncopyable
{
  public:
    CacheConnGuard(CacheConnPtr&& p) : connPtr_(std::move(p)) {}
    CacheConnGuard(CacheConnPtr& p) = delete;

  private:
    CacheConnPtr connPtr_;
};

class CacheManager : boost::noncopyable
{
  public:
    CacheManager()
    {
        init();
    }
    CacheManager* instance()
    {
        static CacheManager T;
        return &T;
    }

  private:
    void init();
};
#endif
