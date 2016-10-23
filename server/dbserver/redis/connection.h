#ifndef _MDUO_SERVER_DBSERVER_REDIS_CONNECTION_H_
#define _MDUO_SERVER_DBSERVER_REDIS_CONNECTION_H_

#include <boost/noncopyable.hpp>
#include <list>
#include <string>
#include <map>
#include <memory>
#include <muduo/base/Timestamp.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/CurrentThread.h>
#include <vector>
#include <assert.h>
#include "hiredis.h"
#include "reply.h"
namespace dbserver
{

class connection;
class connectionGuard;
class redisPool;

typedef std::shared_ptr<connection> connectionPtr; //own the redisContext
typedef std::weak_ptr<connection> connectionWkPtr; //for debug
typedef std::unique_ptr<connectionGuard> connectionGuardPtr; //return this smartpoint to user

class connection : boost::noncopyable
{
public:
    connection(redisPool* pool, redisContext* context)
    : pool_(pool), context_(context), holder_()
    {
        assert(pool);
    }
    ~connection()
    {
        assert(context_);
        redisFree(context_);
    }
    //redisContext* getContext() const { return context_; }
    //redisPool* getPool() const { return pool_; }

private:
    void unassignHolder()
    {
        holder_ = 0;
        getTime_ = muduo::Timestamp::now();
    }
    void assignHolder()
    {
        getTime_ = muduo::Timestamp::now();
        holder_ = muduo::CurrentThread::tid();
    }
    redisPool* pool_;
    redisContext* context_;

    //holder_ and getTime_ for debug 
    pid_t holder_;  
    muduo::Timestamp getTime_;
    friend class connectionGuard;
};

class connectionGuard : boost::noncopyable
{
public:
    connectionGuard(connectionPtr&& p)
    : connPtr_(std::move(p)) {
        connPtr_->assignHolder();
    }
    ~connectionGuard();
    connectionGuard(connectionPtr& p) = delete; //only use rvalue
    //get
    redisContext* getContext() const 
    {
        assert(connPtr_);
        return connPtr_->context_;
    }

    redisPool* getPool() const 
    {
        assert(pool_);
        return connPtr_->pool_;
    }

    reply get_reply();
    std::vector<reply> get_replies(size_t count);
    //command
    int append(const std::vector<std::string>& args);
    reply run(const std::vector<std::string>& args)
    {
        append(args);
        return get_reply();
    }

private:
    connectionPtr connPtr_;
};
}
#endif //_MDUO_SERVER_DBSERVER_REDIS_CONNECTION_H_