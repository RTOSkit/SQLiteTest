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
 * @version 0.3.0a
 * @author Maurizio Spoto ::RTOSkit::
 */

#include "sqlite.h"
#include <QDir>
#include <QElapsedTimer>


SQLite::SQLite(){
    sqlPreferences = new SqlPreferences();
}

void SQLite::startDriver(void){
    QString queryStr ="";

    if(db.isOpen())db.close();

    QString pathDB  = QApplication::applicationDirPath() + DEFAULT_DBNAME;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathDB);
    db.open();

    if(sqlPreferences->useExistDB){
        queryStr = "CREATE TABLE IF NOT EXISTS " + qApp->tr(DEFAULT_TABLENAME) + " (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " \
        "FIELD1 TEXT, FIELD2 TEXT,FIELD3 TEXT,FIELD4 TEXT,FIELD5 TEXT,FIELD6 TEXT," \
        "FIELD7 TEXT,FIELD8 TEXT,FIELD9 TEXT,FIELD10 TEXT);";
    }else{
        queryStr = "CREATE TABLE " + qApp->tr(DEFAULT_TABLENAME) + " (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " \
        "FIELD1 TEXT, FIELD2 TEXT,FIELD3 TEXT,FIELD4 TEXT,FIELD5 TEXT,FIELD6 TEXT," \
        "FIELD7 TEXT,FIELD8 TEXT,FIELD9 TEXT,FIELD10 TEXT);";
    }
    db.exec(queryStr);

    if(sqlPreferences->useRamDB){
        QString sqlAttach = QString("ATTACH DATABASE '%1' AS ramDB").arg(":memory:");
        db.exec(sqlAttach);
        queryStr = "CREATE TABLE ramDB." + qApp->tr(DEFAULT_TABLENAME) + " (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " \
        "FIELD1 TEXT, FIELD2 TEXT,FIELD3 TEXT,FIELD4 TEXT,FIELD5 TEXT,FIELD6 TEXT," \
        "FIELD7 TEXT,FIELD8 TEXT,FIELD9 TEXT,FIELD10 TEXT);";
        db.exec(queryStr);
    }
    db.close();
}

void SQLite::pragmasSet(void){
    if(sqlPreferences->useCustomPageSize)
       db.exec("PRAGMA page_size = " + sqlPreferences->customPageSize);
    if(sqlPreferences->useCustomCacheSize)
       db.exec("PRAGMA cache_size = " + sqlPreferences->customCacheSize);
    if(sqlPreferences->useCustomTempStore)
       db.exec("PRAGMA temp_store = " + sqlPreferences->customTempStore);
    if(sqlPreferences->useCustomJournalMode)
       db.exec("PRAGMA journal_mode = " + sqlPreferences->customJournalMode);
    if(sqlPreferences->useCustomLockingMode)
       db.exec("PRAGMA locking_mode = " + sqlPreferences->customLockingMode);
    if(sqlPreferences->useCustomSynchronous)
       db.exec("PRAGMA synchronous = " + sqlPreferences->customSynchronous);
}


void SQLite::speedTests(void){
    QStringList data;
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");
    data.append("testa");

    db.exec("BEGIN TRANSACTION;");

    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    ctrlTimer.start();
    for(int i=0;i<20;i++){

/*      //PREPARE MODE  (20 records > 2 ms)
        QSqlQuery qInsert(db);
        qInsert.prepare("INSERT INTO " + qApp->tr(DEFAULT_TABLENAME) + " (FIELD1, FIELD2, FIELD3, FIELD4, FIELD5, FIELD6, FIELD7, FIELD8, FIELD9, FIELD10) VALUES (:FIELD1, :FIELD2, :FIELD3, :FIELD4, :FIELD5, :FIELD6, :FIELD7, :FIELD8, :FIELD9, :FIELD10)");
        qInsert.bindValue(":FIELD1", "testc");
        qInsert.bindValue(":FIELD2", "testc");
        qInsert.bindValue(":FIELD3", "testc");
        qInsert.bindValue(":FIELD4", "testc");
        qInsert.bindValue(":FIELD5", "testc");
        qInsert.bindValue(":FIELD6", "testc");
        qInsert.bindValue(":FIELD7", "testc");
        qInsert.bindValue(":FIELD8", "testc");
        qInsert.bindValue(":FIELD9", "testc");
        qInsert.bindValue(":FIELD10", "testc");
        qInsert.exec();
*/

/*      //DIRECT QUERY MODE (20 records > 1 ms)
      db.exec("INSERT INTO " + qApp->tr(DEFAULT_TABLENAME) + " (FIELD1, FIELD2, FIELD3, FIELD4, FIELD5, FIELD6, FIELD7, FIELD8, FIELD9, FIELD10) VALUES ('TEST', 'TEST', 'TEST', 'TEST', 'TEST', 'TEST', 'TEST', 'TEST', 'TEST', 'TEST');");
*/

/*
    //DIRECT QUERY MODE  with Array (20 records > 1 ms)
      db.exec("INSERT INTO " + qApp->tr(DEFAULT_TABLENAME) +
              " (FIELD1, FIELD2, FIELD3, FIELD4, FIELD5, FIELD6, FIELD7, FIELD8, FIELD9, FIELD10) VALUES " +
              "('" + data[0] + "', '" + data[1] + "', '" + data[2] + "', '" + data[3] + "', '" + data[4] + "', '" + data[5] + "', '" + data[6] + "', '" + data[7] + "', '" + data[8] + "', '" + data[9] + "');");
*/



    }
    ctrlMS= ctrlTimer.elapsed();
    db.exec("COMMIT;");
    db.close();


    QString strCtrlMS="";
    strCtrlMS.sprintf("Total Insert in %u MS",ctrlMS);
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strCtrlMS,
    QMessageBox::Ok);
}

void SQLite::dbFlush(void){
    if(db.isOpen())db.close();
    QSqlDatabase::removeDatabase("QSQLITE");
}

void SQLite::dbClose(void){        
    if(sqlPreferences->useAtomicCommit)
       db.exec("COMMIT;");
    if(db.isOpen())db.close();
}

void SQLite::dbOpen(void){    
    if(!db.isOpen())db.open();
    if(sqlPreferences->useAtomicCommit){
       pragmasSet();
       db.exec("BEGIN TRANSACTION;");
    }
}


bool SQLite::updateDBRecord(QStringList data){     
     QString queryStr = "UPDATE " + qApp->tr(DEFAULT_TABLENAME) + " SET "
                       + "FIELD1 = '"   + data[0] + "', "
                       + "FIELD2 = '"   + data[1] + "', "
                       + "FIELD3 = '"   + data[2] + "', "
                       + "FIELD4 = '"   + data[3] + "', "
                       + "FIELD5 = '"   + data[4] + "', "
                       + "FIELD6 = '"   + data[5] + "', "
                       + "FIELD7 = '"   + data[6] + "', "
                       + "FIELD8 = '"   + data[7] + "', "
                       + "FIELD9 = '"   + data[8] + "', "
                       + "FIELD10 = '"   + data[9] + "', "
                       + "WHERE FIELD1 = '" + data[0] + "'";
    QSqlQuery query(queryStr,db);
    return (bool) query.result();
}


bool SQLite::insertDBRecord(QStringList data){     
     QString queryStr = "INSERT INTO " + qApp->tr(DEFAULT_TABLENAME) + " (FIELD1,FIELD2,FIELD3,FIELD4,FIELD5,FIELD6,FIELD7,FIELD8,FIELD9,FIELD10) VALUES ("
             + "'" + data[1] + "', "
             + "'" + data[2] + "', "
             + "'" + data[3] + "', "
             + "'" + data[4] + "', "
             + "'" + data[5] + "', "
             + "'" + data[6] + "', "
             + "'" + data[7] + "', "
             + "'" + data[8] + "', "
             + "'" + data[9] + "', "
             + "'" + data[10] + "' )";     
    QSqlQuery query(queryStr,db);
    return (bool) query.result();
}


bool SQLite::deleteDBRecord(){     
     QString queryStr = "DELETE FROM " + qApp->tr(DEFAULT_TABLENAME) + " WHERE rowid= (SELECT MIN(rowid) FROM " + qApp->tr(DEFAULT_TABLENAME) + ");";
     QSqlQuery query(queryStr,db);
     return (bool) query.result();
}


QStringList SQLite::selectDBRecord(QString startIdx){
     QStringList sl;
     QString querySql = "SELECT * FROM " + qApp->tr(DEFAULT_TABLENAME) + " LIMIT " + startIdx + ",1;";
     QSqlQuery query(querySql,db);
     query.next();
     sl << query.value(1).toString();sl << query.value(2).toString();
     sl << query.value(3).toString();sl << query.value(4).toString();
     sl << query.value(5).toString();sl << query.value(6).toString();
     sl << query.value(7).toString();sl << query.value(8).toString();
     sl << query.value(9).toString();sl << query.value(10).toString();
     return sl;
}
