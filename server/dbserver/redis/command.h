#ifndef _MUDUO_SERVER_DBSERVER_REDIS_COMMAND_H_
#define _MUDUO_SERVER_DBSERVER_REDIS_COMMAND_H_
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace dbserver
{
class redisCommand
{
public:
    redisCommand(string s) { command_.push_back(std::move(s)); }
    redisCommand(const string& s) { command_.push_back(s); }
    redisCommand(string&& s) { command_.push_back(std::move(s)); }

    template <typename T>
    inline redisCommand& operator<<(const T type)
    {
        command_.push_back(std::to_string(type));
        return *this;
    }

    template <typename T>
    inline redisCommand& operator()(const T type)
    {
        command_.push_back(std::to_string(type));
        return *this;
    }
    operator vector<string>&() { return command_; }
    string debugString() const
    {
        string ret("[redis command:(");
        bool first = true;
        for (auto& i : command_)
        {
            if (!first)
            {
                ret += ",";
            }
            first = false;
            ret += "'" + i + "'";
        }
        ret += ")]";
    }

private:
    vector<string> command_;
};
}
#endif