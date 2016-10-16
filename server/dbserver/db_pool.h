#ifndef _MUDUO_SERVER_DBSERVER_H_
#define _MUDUO_SERVER_DBSERVER_H_
#include <string>
#include <mysql.h>
#include <boost/noncopyable.hpp>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Condition.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/Logging.h>
namespace dbserver
{

using std::string;
using std::vector;

class DBConn;
class DBConnGuard;
typedef std::shared_ptr<DBConn> DBConnPtr;
typedef std::weak_ptr<DBConn> DBConnWkPtr;
typedef std::unique_ptr<DBConnGuard> DBConnGuardPtr;

enum
{
    MYSQL_MASTER = 0,
    MYSQL_SLAVE = 1
};

class DBPool : boost::noncopyable
{
public:
    DBPool(const string& ip, const string& username, const string& passwd,
        const string& dbname, int port, int max_con);
    ~DBPool();
    // get a mysql connection form pool
    DBConnGuardPtr getConnection();
    void relConnection(DBConnPtr&& p);

private:
    DBConnPtr createConnection();
    string ip_;
    string username_;
    string passwd_;
    string dbname_;
    int port_;
    int max_con_;

    muduo::MutexLock mutex_;
    muduo::Condition notFree_;
    int use_con_;
    typedef std::list<DBConnPtr> DBCOnnList;
    typedef std::list<DBConnWkPtr> DBCOnnWkList; // user check connection expired

    DBCOnnList conlist_;
    DBCOnnWkList conWklist_;
}; // class DBPool

class DBManager : boost::noncopyable
{
public:
    // typedef std::map<string, DBPool *> PoolMap;
    DBManager() { init(); }
    ~DBManager() { delete master_; }
    static DBManager* instance()
    {
        static DBManager T;
        return &T;
    }
    DBConnGuardPtr getDBConn(int index)
    {
        if (index == MYSQL_MASTER)
        {
            return master_->getConnection();
        }
        else if (index == MYSQL_SLAVE)
        {
            return slave_->getConnection();
        }
        assert(0);
        return nullptr;
    }

private:
    void init();
    DBPool* master_;
    DBPool* slave_; // TODO if the number of slave >2
    // PoolMap poolmap_;
};
class DBConn : boost::noncopyable
{
public:
    DBConn(DBPool* pool, MYSQL* mysql)
    : pool_(pool), mysql_(mysql), connected_(true),
      getTime_(muduo::Timestamp::now()) {}
    ~DBConn() { ::mysql_close(mysql_); }
    void resetTime() { getTime_ = muduo::Timestamp::now(); }
    muduo::Timestamp getTime() { return getTime_; }
    DBPool* getPool() { return pool_; }
    MYSQL* getMysql() { return mysql_; }
    bool getConnected() { return connected_; }
    void setConnected(bool b) { connected_ = b; }

private:
    DBPool* pool_;
    MYSQL* mysql_;
    bool connected_;
    muduo::Timestamp getTime_;
};

class DBConnGuard : boost::noncopyable
{
public:
    explicit DBConnGuard(DBConnPtr&& pConn)
    : pConn_(std::move(pConn))
    {
        pConn_->resetTime();
    }
    DBConnGuard(DBConnPtr&) = delete;
    ~DBConnGuard() { pConn_->getPool()->relConnection(std::move(pConn_)); }

    bool ping();
    int query(const string& command);
    int getQueryResults(const string& command,
        std::vector<std::vector<string>>* results,
        std::vector<string>* fields);
    int getResults(vector<vector<string>>* results, vector<string>* fields);

private:
    DBConnPtr pConn_;
}; // class DBConnGuard

// return DBConnGuardPtr to the user
}
#endif