#ifndef _MUDUO_SERVER_DBSERVER_CACHEPOOL_H
#define _MUDUO_SERVER_DBSERVER_CACHEPOOL_H

#include <boost/noncopyable.hpp>
#include <list>
#include <mysql.h>
#include <string>

#include <map>
#include <memory>
#include <muduo/base/Condition.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/InetAddress.h>
#include <vector>
#include "hiredis.h"

enum CachePoolIndex
{

};
//#include <muduo/base/Logging.h>
class CacheConn;
class CacheConnGuard;

using std::string;
using std::vector;
using std::map;

using muduo::Timestamp;
using muduo::MutexLock;

typedef std::shared_ptr<CacheConn> CacheConnPtr;
typedef std::weak_ptr<CacheConn> CacheConnWkPtr;
typedef std::unique_ptr<CacheConnGuard> CacheConnGuardPtr;
class CachePool : boost::noncopyable
{
public:
    CachePool(const string& ip, int port, int max_con);
    ~CachePool();
    void relConnection(CacheConnPtr&& p);
    CacheConnGuardPtr getConnection();

private:
    CacheConnPtr createConnection();
    string ip_;
    int port;
    int max_con_;
    int num_con_;
    int db_num_;
    MutexLock mutex_;
    Condition notEmpty_;
    typedef std::list<CacheConn> CacheConnList;
    typedef std::list<CacheConnWkPtr> CacheConnWkList; // user check connection expired

    CacheConnList conlist_;
    CacheConnWkList conWklist_;
};

class CacheConn : boost::noncopyable
{
public:
    CacheConn(CachePool* pool, redisContext* context)
    : pool_(pool), context_(context) {}
    ~CacheConn()
    {
        assert(context_);
        redisFree(context_);
    }
    redisContext* getContext()const {return context_;}
    CachePool* getPool() const { return pool_; }

private:
    CachePool* pool_;
    redisContext* context_;
};
class CacheConnGuard : boost::noncopyable
{
public:
    CacheConnGuard(CacheConnPtr&& p)
    : connPtr_(std::move(p)) {}
    ~CacheConnGuard()
    {
        //reset time
        connPtr_->getPool()->relConnection(std::move(connPtr_));
    }
    CacheConnGuard(CacheConnPtr& p) = delete;//only use rvalue

    string get(const string &key);
    string setex(const string &key,int timeout,const string &value);
    string set(const string &key,const string &value);
    bool mget(vector<string> &keys,map<string,string> &ret_values);
    bool isExists(const string &keys);
    uint64_t hdel(const string &key,const string &field);
    string   hget(const string &key,const string &field);
    bool     hgetAll(const string,map<string,string> &ret_values);
    uint64_t hset(const string &key,const string& field,const string &value);
    string hmset(const string &key,map<string,string> &hash);
    bool hmget(const string &key,const vector<string> &fields,vector<string> &values);
    uint64_t lpush(const string &key,const string &value);
    uint64_t rpush(const string &key,const string &value);
    uint64_t llen(const string &key);
    bool lrange(const string&key,uint64_t start,uint64_t end,vector<string> &re_values);

private:
    CacheConnPtr connPtr_;
};

class CacheManager : boost::noncopyable
{
public:
    CacheManager() { init(); }
    CacheConnGuardPtr getCacheConn(const string& name);
    CacheManager* instance()
    {
        static CacheManager T;
        return &T;
    }
private:
    void init();
};
#endif
