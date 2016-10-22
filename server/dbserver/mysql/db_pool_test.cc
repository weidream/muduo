#include "db_pool.h"
#include <iostream>
using namespace dbserver;
using namespace std;
int main()
{
    DBManager::instance();
    DBConnGuardPtr p = DBManager::instance()->getDBConn(0);
    vector<vector<string>> vv;
    vector<string> ff;
    p->getQueryResults("select * from student;", &vv, &ff);
    cout << "vv size =" << vv.size() << endl;
    cout << "ff size =" << ff.size() << endl;
    for (auto& i : ff)
        cout << i << "  ";
    cout << endl;
    for (auto& i : vv)
    {
        for (auto& j : i)
        {
            cout << j << "  ";
        }
        cout << endl;
    }
    return 0;
}