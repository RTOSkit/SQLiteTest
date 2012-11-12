/**
 * SQLiteTest - Analysis Tools Kit
 *
 * **
 * Copyright (c) 2012 Emmodded Project
 * All rights reserved.
 *
 * This code is derived from software contributed to Emmodded Project
 * by Maurizio Spoto <mspoto@emmodded.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY EMMODDED PROJECT AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @package sqlitetest
 */

#ifndef SQLITE_H
#define SQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QStringList>
#include <QString>
#include <QVariant>
#include <QHash>


#define DEFAULT_DBNAME             "/testdb.db3"
#define DEFAULT_TABLENAME          "testdb"

typedef struct{

    bool useAtomicCommit;
    bool useCustomPageSize;
    bool useCustomCacheSize;
    bool useCustomTempStore;
    bool useCustomJournalMode;
    bool useCustomLockingMode;
    bool useCustomSynchronous;
    bool useExistDB;
    bool useRamDB;
    QString customPageSize;
    QString customCacheSize;
    QString customTempStore;
    QString customJournalMode;
    QString customLockingMode;
    QString customSynchronous;

}SqlPreferences;

class SQLite
{
public:
    SQLite();
    void startDriver(void);
    void dbOpen(void);
    void dbClose(void);
    void dbFlush(void);
    bool updateDBRecord(QStringList data);
    bool insertDBRecord(QStringList data);    

    QSqlDatabase db;
    SqlPreferences *sqlPreferences;


private:
    void speedTests(void);
    void pragmasSet(void);
};

#endif // SQLITE_H
