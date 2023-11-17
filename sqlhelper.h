#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <Qt>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace SQLHelper {
    QString generateArrayBinds(QString prefix, const QStringList& list, QHash<QString, QVariant>& binds);
    void applyBindMaps(QSqlQuery& query, const QHash<QString, QVariant>& binds);
    void initializeDatabase(QSqlDatabase& db);
    void clearDatabase(QSqlDatabase& db);
    QString generateId(const QString& table, const QString &primaryKey, const QString& prefix);
}

#endif // SQLHELPER_H
