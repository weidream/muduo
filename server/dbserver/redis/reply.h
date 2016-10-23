#ifndef _MUDUO_SERVER_DBSERVER_REDIS_H_
#define _MUDUO_SERVER_DBSERVER_REDIS_H_
#include <vector>
#include <string>
#include "hiredis.h"
#include "connection.h"

class connection;
class connectionGuard;
class reply
{
public:
    /*
#define REDIS_REPLY_STRING 1
#define REDIS_REPLY_ARRAY 2
#define REDIS_REPLY_INTEGER 3
#define REDIS_REPLY_NIL 4
#define REDIS_REPLY_STATUS 5
#define REDIS_REPLY_ERROR 6
*/
    enum class type_t
    {
        STRING = 1,
        ARRAY = 2,
        INTEGER = 3,
        NIL = 4,
        STATUS = 5,
        ERROR = 6
    };
    type_t type() const { return type_; }
    uint64_t integer() const { return integer_; }
    const std::string& str() const { return str_; }
    const std::vector<reply>& element() const { return element_; }


//    reply(reply&& rvalue){
//    }
    reply(redisReply* r)
    : type_(type_t::ERROR), integer_(0)
    {
        type_ = static_cast<type_t>(r->type);
        switch (type_)
        {
            case type_t::ERROR:
            case type_t::STATUS:
            case type_t::STRING:
            {
                str_ = std::string(r->str, r->len);
            }
            break;
            case type_t::INTEGER:
            {
                integer_ = static_cast<uint64_t>(r->integer);
            }
            break;
            case type_t::ARRAY:
            {
                for (size_t i = 0; i < r->elements; i++)
                {
                    element_.push_back(reply(r->element[ i ]));
                }
            }
            break;
            default:
                break;
        }
    }
    reply()
    : type_(type_t::ERROR), integer_(0) {}
private:
    type_t type_;
    uint64_t integer_;
    std::string str_;
    std::vector<reply> element_;

    friend class connection;
    friend class connectionGuard;
};

/* This is the reply object returned by redisCommand() */
//typedef struct redisReply {
//    int type; /* REDIS_REPLY_* */
//    long long integer; /* The integer when type is REDIS_REPLY_INTEGER */
//    int len; /* Length of string */
//    char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
//    size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
//    struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
//} redisReply;

#endif
