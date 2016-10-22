#include "cache_pool.h"


string CacheConnGuard::get(const string& key)
{
    redisReply* reply = (redisReply *)redisCommand(m_pContext, "GET %s", key.c_str());
    if(reply){
        
    }
}
string CacheConnGuard::setex(const string& key, int timeout, const string& value)
{
}
string CacheConnGuard::set(const string& key, const string& value)
{
}
bool CacheConnGuard::mget(vector<string>& keys, map<string, string>& ret_values)
{
}
bool CacheConnGuard::isExists(const string& keys)
{
}
uint64_t CacheConnGuard::hdel(const string& key, const string& field)
{
}
string CacheConnGuard::hget(const string& key, const string& field)
{
}
bool CacheConnGuard::hgetAll(const string, map<string, string>& ret_values)
{
}
uint64_t CacheConnGuard::hset(const string& key, const string& field, const string& value)
{
}
string CacheConnGuard::hmset(const string& key, map<string, string>& hash)
{
}
bool CacheConnGuard::hmget(const string& key, const vector<string>& fields, vector<string>& values)
{
}
uint64_t CacheConnGuard::lpush(const string& key, const string& value)
{
}
uint64_t CacheConnGuard::rpush(const string& key, const string& value)
{
}
uint64_t CacheConnGuard::llen(const string& key)
{
}
bool CacheConnGuard::lrange(const string& key, uint64_t start, uint64_t end, vector<string>& re_values)
{
}

//CachePool
CachePool::CachePool(const string& ip, int port, int max_con, int db_num)
: ip_(ip), port_(port), max_con_(max_con), num_con_(0), db_num_(db_num), mutex_(), notFree_(mutex_)
{
    for (int i = 0; i < max_con_ / 2; i++)
    {
        CacheConnPtr p = createConnection();
        if (p)
        {
            conWklist_.push_back(p);
            conlist_.push_back(std::move(p));
        }
    }
}

CachePool::~CachePool()
{
    for (auto& i : conlist_)
        i.reset();
}
void CachePool::relConnection(CacheConnPtr&& p)
{
    MutexLockGuard lock(mutex_);
    conlist_.push_back(std::move(p));
    notFree_.notify();
}

CacheConnGuardPtr CachePool::getConnection();
{
    MutexLockGuard lock(mutex_);
    while (conlist_.empty())
    {
        if (max_con_ > num_con_)
        {
            CacheConnPtr p = createConnection();
            return CacheConnGuardPtr(new CacheConnGuard(std::move(p)));
        }
        else
        {
            notFree_.wait();
        }
    }
    CacheConnPtr pConn = conlist_.front();
    conlist_.pop_front();
    return CacheConnGuardPtr(new CacheConnGuard(std::move(pConn)));
}

CacheConnPtr CachePool::createConnection()
{
    struct timeval timeout = {0, 200000}; //200ms
    redisContext* context = redisConnectWithTimeout(ip_.c_str(), static_cast<int16_t>(port_), timeout);
    if (!context || context->err)
    {
        //error debug
        if (context)
        {
            //debug context->errstr
        }
        return nullptr;
    }
    redisReply* reply = ( redisReply* )redisCommand(context, "SELECT %d", m_pCachePool->GetDBNum());
    if (reply && (reply->type == REDIS_REPLY_STATUS) && (strncmp(reply->str, "OK", 2) == 0))
    {
        freeReplyObject(reply);
    }
    else
    {
        //debug error
        redisFree(context);
        return nullptr;
    }
    num_con_++;
    return make_shared<CacheConn>(this, context);
}