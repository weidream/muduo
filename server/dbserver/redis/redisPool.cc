#include "redisPool.h"
namespace dbserver
{
using namespace muduo;

redisPool::redisPool(const string& ip, int port, int max_con, int db_num)
: ip_(ip), port_(port), max_con_(max_con), num_con_(0), db_num_(db_num), mutex_(), notFree_(mutex_)
{
    for (int i = 0; i < max_con_ / 2; i++)
    {
        connectionPtr p = createConnection();
        if (p)
        {
            conWklist_.push_back(p);
            conlist_.push_back(std::move(p));
        }
    }
}

redisPool::~redisPool()
{
    for (auto& i : conlist_)
        i.reset();
}
void redisPool::relConnection(connectionPtr&& p)
{
    MutexLockGuard lock(mutex_);
    conlist_.push_back(std::move(p));
    notFree_.notify();
}

connectionGuardPtr redisPool::getConnection()
{
    MutexLockGuard lock(mutex_);
    while (conlist_.empty())
    {
        if (max_con_ > num_con_)
        {
            connectionPtr p = createConnection();
            return connectionGuardPtr(new connectionGuard(std::move(p)));
        }
        else
        {
            notFree_.wait();
        }
    }
    connectionPtr pConn = conlist_.front();
    conlist_.pop_front();
    return connectionGuardPtr(new connectionGuard(std::move(pConn)));
}

connectionPtr redisPool::createConnection()
{
    struct timeval timeout = {0, 200000}; //200ms
    redisContext* context = redisConnectWithTimeout(ip_.c_str(), static_cast<int16_t>(port_), timeout);
    if (!context || context->err)
    {
        //TODO error debug
        if (context)
        {
            //TODO debug context->errstr
            redisFree(context);
        }
        return nullptr;
    }
    string scom = "SELECT ";
    scom += std::to_string(db_num_);
    redisReply* reply = static_cast<redisReply *>(redisCommand(context, "SELECT %d",db_num_));
    if (reply && (reply->type == REDIS_REPLY_STATUS) && (strncmp(reply->str, "OK", 2) == 0))
    {
        freeReplyObject(reply);
    }
    else
    {
        //TODO debug error
        freeReplyObject(reply);
        redisFree(context);
        return nullptr;
    }
    num_con_++;
    return std::make_shared<connection>(this, context);
}
}