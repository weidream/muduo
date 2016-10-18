
#include "db_pool.h"
#include "db_errdef.h"
// DBConn
#include <muduo/base/Logging.h>
namespace dbserver
{
using std::vector;
using namespace muduo;
using namespace muduo::net;
namespace muduo
{
class MutexLockGuard;
}
bool DBConnGuard::ping()
{

    if (mysql_ping(pConn_->getMysql()) != 0)
    {
        pConn_->setConnected(false);
    }
    return pConn_->getConnected();
}

int DBConnGuard::getQueryResults(const string& command,
    vector<vector<string>>* results,
    vector<string>* fields)
{
    int ret = query(command);
    if (ret)
        return ret;
    return getResults(results, fields);
}

int DBConnGuard::getResults(vector<vector<string>>* results,
    vector<string>* fields)
{
    MYSQL_RES* result = mysql_store_result(pConn_->getMysql());
    if (result)
    {
        size_t row_count = static_cast<size_t>(result->row_count);
        size_t field_count = static_cast<size_t>(result->field_count);
        if (fields)
        {
            for (size_t i = 0; i < field_count; i++)
            {
                fields->push_back(result->fields[ i ].name);
            }
        }
        for (size_t i = 0; i < row_count; i++)
        {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (!row)
                break;
            vector<string> result_row;
            for (size_t j = 0; j < field_count; j++)
            {
                result_row.push_back(row[ j ] ? row[ j ] : "");
            }
            results->push_back(std::move(result_row));
        }
        mysql_free_result(result);
    }
    return OK;
}

int DBConnGuard::query(const string& command)
{
    int ret = mysql_query(pConn_->getMysql(), command.c_str());
    if (OK != ret)
    {
        if (ret < 0)
        {
            return MYSQL_FAIL;
        }
        else
        {
            return MYSQL_NODATA;
        }
    }
    return ret;
}

// DBPool
DBPool::DBPool(const string& ip, const string& username, const string& passwd,
    const string& dbname, int port, int max_con)
: ip_(ip),
  username_(username),
  passwd_(passwd),
  dbname_(dbname),
  port_(port),
  max_con_(max_con),
  mutex_(),
  notFree_(mutex_)
{
    assert(max_con > 0);
    for (int i = 0; i < max_con / 2; i++)
    {
        DBConnPtr pConn = createConnection();
        if (pConn)
        {
            conWklist_.push_back(pConn);
            conlist_.push_back(std::move(pConn));
        }
    }
}

DBPool::~DBPool()
{
    for (auto& i : conlist_)
        i.reset();
}

DBConnPtr DBPool::createConnection()
{
    int timeout = 5;

    MYSQL* mysql = mysql_init(NULL);
    if (NULL == mysql)
    {
        return nullptr;
    }
    mysql_options(mysql, MYSQL_OPT_READ_TIMEOUT, reinterpret_cast<char*>(&timeout));
    mysql_options(mysql, MYSQL_OPT_WRITE_TIMEOUT, reinterpret_cast<char*>(&timeout));

    int opt = 1;
    mysql_options(mysql, MYSQL_OPT_RECONNECT, reinterpret_cast<char*>(&opt));

    if (!mysql_real_connect(mysql, ip_.c_str(), username_.c_str(),
            passwd_.c_str(), dbname_.c_str(),
            static_cast<uint16_t>(port_), 0, 0))
    {
        mysql_close(mysql);
        mysql = NULL;
        //TODO DEBUG
        return nullptr;
    }
    use_con_++;
    return std::make_shared<DBConn>(this, mysql);
}

DBConnGuardPtr DBPool::getConnection()
{
    MutexLockGuard lock(mutex_);
    while (conlist_.empty())
    {
        if (max_con_ > use_con_)
        {
            DBConnPtr p = createConnection();
            return DBConnGuardPtr(new DBConnGuard(std::move(p)));
        }
        else
        {
            notFree_.wait();
        }
    }
    DBConnPtr pConn = conlist_.front();
    conlist_.pop_front();
    return DBConnGuardPtr(new DBConnGuard(std::move(pConn)));
}

void DBPool::relConnection(DBConnPtr&& p)
{
    MutexLockGuard lock(mutex_);
    conlist_.push_back(std::move(p));
}

// DBManager

void DBManager::init()
{
    //only for test
    //
    string username("root");
    string passwd("weigd");
    string ipAddr("127.0.0.1");
    string dbname("sampdb");
    master_ = new DBPool(ipAddr, username, passwd, dbname, 3306, 8);
}

} // dbserver