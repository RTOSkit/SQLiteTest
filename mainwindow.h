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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QCheckBox>
#include <QElapsedTimer>
#include <QTimer>
#include <math.h>
#include "sqlite.h"
#include "helpsetdialog.h"
#include "aboutdialog.h"
#include "resultdialog.h"

#define FIX_NR_FIELDS    10
#define TEXT_FIELD_SIZE  1000
#define MAX_RECORDS      5000
#define MAX_TURNS        30
#define MAX_SLEEPS       30
#define RRL_TITLE        "Ram Records List "

typedef void (*AnonymVoid)();

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SQLite* sqlite;
    int postTmpNrecords;
    int postTmpRunSeconds;
    bool fullSpeed;
    int RRLbytes;
    QList<int> resultTimes;

    
public slots:
    void setValueEPS(int value);
    void setValueST(int value);
    void ChangeFFGfieldType(int);
    void ChangeFFGfieldContent(int);
    void ClickedClear();
    void ClickedMake();
    void ClickedTESTINSERT();
    void ClickedTESTUPDATE();
    void ClickedTESTDELETE();
    void ClickedTESTSELECT();
    void about();
    void open();
    void runTimerEvent();



private:    
    Ui::MainWindow *ui;
    void timerEvent(QTimerEvent *);
    void initVectors(void);
    void initListeners(void);
    void createActions();
    void createMenus();
    void openSet(bool firstCall);
    QString randomFixString(int lenght);    
    void insertInvoke(void);
    void insertInvokeFullSpeed(void);
    void startRunTimer();
    void callAnonymTask(void(MainWindow::*)());
    void openResult();
    void stopProcess();

    QSpinBox* sbxLenghtVector[FIX_NR_FIELDS];
    QCheckBox* cbxTextFieldVector[FIX_NR_FIELDS];
    QCheckBox* cbxRandomContentVector[FIX_NR_FIELDS];
    QLineEdit* txtTextContentVector[FIX_NR_FIELDS];
    QStringList dataDB[MAX_RECORDS];    
    int resultTimesIdx;
    int lastTime;
    int sleepTime;
    int tmpNrecords;          
    bool muteEvent;    
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QTimer *runTimer;
    int tmpRunSeconds;
    AnonymVoid runFunction;
    bool isBusy;
    int mainTimer;
};

#endif // MAINWINDOW_H
