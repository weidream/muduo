#ifndef _MUDUO_SERVER_DBSERVER_REDIS_COMMAND_H_
#define _MUDUO_SERVER_DBSERVER_REDIS_COMMAND_H_
#include <string>
#include <vector>
using std::vector;
using std::string;

namespace dbserver
{
template <class T>
using void_t = void;

class Command
{
public:
    Command() {}
    Command(const string& s) { command_.push_back(s); }
    Command(string&& s) { command_.push_back(std::move(s)); }
    Command(const char* s) { command_.push_back(std::string(s)); }
    ~Command();

    template <typename T, typename = void_t<decltype(std::to_string(std::declval<T>()))>>
    Command& operator<<(T&& t)
    {
        command_.push_back(std::to_string(t));
        return *this;
    }

    Command& operator<<(const string& v)
    {
        command_.push_back(v);
        return *this;
    }

    Command& operator<<(string&& v)
    {
        command_.push_back(std::move(v));
        return *this;
    }
    //opeator ()
    template <typename T, typename = void_t<decltype(std::to_string(std::declval<T>()))>>
    Command& operator()(T&& t)
    {
        command_.push_back(std::to_string(t));
        return *this;
    }

    Command& operator()(const string& v)
    {
        command_.push_back(v);
        return *this;
    }

    Command& operator()(string&& v)
    {
        command_.push_back(std::move(v));
        return *this;
    }

    operator vector<string>&()
    {
        return command_;
    }

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