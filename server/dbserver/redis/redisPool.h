#ifndef _MUDUO_SERVER_DBSERVER_redisPool_H
#define _MUDUO_SERVER_DBSERVER_redisPool_H

#include <boost/noncopyable.hpp>
#include <list>
//#include <mysql.h>
#include <string>

#include <map>
#include <memory>
#include <muduo/base/Condition.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/InetAddress.h>
#include <vector>

#include "hiredis.h"
#include "connection.h"
namespace dbserver{
    
using std::string;
using std::vector;
using std::map;

using muduo::Timestamp;
using muduo::MutexLock;
using muduo::Condition;

class redisPool : boost::noncopyable
{
public:
    redisPool(const string& ip, int port, int max_con,int db_num);
    ~redisPool();
    void relConnection(connectionPtr&& p);
    connectionGuardPtr getConnection();
private:
    connectionPtr createConnection();
    string ip_;
    int port_;
    int max_con_;
    int num_con_;
    int db_num_;
    MutexLock mutex_;
    Condition notFree_;
    typedef std::list<connectionPtr> connectionList;
    typedef std::list<connectionWkPtr> connectionWkList; // user check connection expired

    connectionList conlist_;
    connectionWkList conWklist_;
};

class CacheManager : boost::noncopyable
{
public:
    CacheManager() { init(); }
    connectionGuardPtr getconnection(const string& name);
    CacheManager* instance()
    {
        static CacheManager T;
        return &T;
    }

private:
    void init();
};
}
#endif
