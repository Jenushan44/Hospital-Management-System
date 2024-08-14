#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class DbManager {
public:
    DbManager(const QString& path);
    bool addPatient(const QString& healthCardNumber, const QString& firstName, const QString& lastName, const QString& dateOfBirth, const QString& gender, const QString& bloodType, const QString& address, const QString& phoneNumber);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
