#ifndef DB_H
#define DB_H

#include <QSqlDatabase>

class DB
{
public:
    DB();
    static bool connect();

private:
    static QSqlDatabase db;
};

#endif // DB_H
