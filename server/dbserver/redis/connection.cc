#include "connection.h"
#include "redisPool.h"
#include "reply.h"
namespace dbserver
{

connectionGuard::~connectionGuard()
{
    connPtr_->unassignHolder();
    connPtr_->pool_->relConnection(std::move(connPtr_));
}

int connectionGuard::append(const std::vector<std::string>& commands)
{
    std::vector<const char*> argv;
    argv.reserve(commands.size());
    std::vector<size_t> argvlen;
    argvlen.reserve(commands.size());

    for (auto& i : commands)
    {
        argv.push_back(i.c_str());
        argvlen.push_back(i.size());
    }
    int ret = redisAppendCommandArgv(connPtr_->context_, static_cast<int>(commands.size()), argv.data(), argvlen.data());
    if (ret != REDIS_OK)
    {
        //TODO debug error
    }
    return ret;
}

reply connectionGuard::get_reply()
{
    redisReply* r;
    int error = redisGetReply(connPtr_->context_, reinterpret_cast<void**>(&r));
    if (error != REDIS_OK)
    {
        //TODO debug error
        freeReplyObject(r);
        return reply();
    }
    reply ret(r);
    freeReplyObject(r);

    if (ret.type() == reply::type_t::ERROR &&
        (ret.str().find("READONLY") == 0))
    {
       //TODO debug error
    }
    return ret;
}

std::vector<reply> connectionGuard::get_replies(size_t count)
{
    std::vector<reply> ret;
    for (size_t i=0; i < count; ++i)
    {
        ret.push_back(get_reply());
    }
    return ret;
}

}