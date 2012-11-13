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

#include "helpsetdialog.h"
#include "ui_helpsetdialog.h"

HelpSetDialog::HelpSetDialog(bool firstCall,QWidget *parent):    
    QDialog(parent),
    ui(new Ui::HelpSetDialog){    
    this->firstCall = firstCall;
    ui->setupUi(this);    
    ClickedHome();
    initListeners();    
    cparent = (MainWindow*)parent;
    ui->cbxUED->setEnabled(firstCall);
    ui->cbxARD->setEnabled(firstCall);
}

HelpSetDialog::~HelpSetDialog(){
    delete ui;
}

void HelpSetDialog::beforeClose(){

    if(firstCall){
        goto lBEFORECLOSE_SET;
    }else{
        QString msg = "Do you want to charge driver with a new configuration profile?";
        if(QMessageBox::question(0, qApp->tr("SQLiteTest"),msg,
                                    QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok){
            goto lBEFORECLOSE_SET;
        }else{
            goto lBEFORECLOSE_EXIT;
        }
    }

lBEFORECLOSE_SET:
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useAtomicCommit =  ui->groupBoxAC->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useCustomPageSize =  ui->gbAC_0->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useCustomCacheSize =  ui->gbAC_1->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customTempStore =  ui->gbAC_2->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useCustomJournalMode =  ui->gbAC_3->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useCustomLockingMode =  ui->gbAC_4->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useCustomSynchronous =  ui->gbAC_5->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useExistDB =  ui->cbxUED->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->useRamDB =  ui->cbxARD->isChecked();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customPageSize =  ui->txtAC_0->text();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customCacheSize =  ui->txtAC_1->text();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customTempStore =  ui->txtAC_2->text();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customJournalMode =  ui->txtAC_3->text();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customLockingMode =  ui->txtAC_4->text();
    ((MainWindow*)cparent)->sqlite->sqlPreferences->customSynchronous =  ui->txtAC_5->text();


lBEFORECLOSE_EXIT:
    asm("nop");
}

void HelpSetDialog::closeEvent(QCloseEvent * event){
    event=event;
    //event->ignore();
    beforeClose();
}

void HelpSetDialog::initListeners(void){
   connect(ui->btnH_home,SIGNAL(clicked()),this,SLOT(ClickedHome()));
   connect(ui->btnH_git,SIGNAL(clicked()),this,SLOT(ClickedGit()));
   connect(ui->btnH_close,SIGNAL(clicked()),this,SLOT(ClickedClose()));
   connect(ui->btnH_back,SIGNAL(clicked()),this,SLOT(ClickedBack()));
   connect(ui->btnH_forward,SIGNAL(clicked()),this,SLOT(ClickedForward()));
   connect(ui->btnH_refresh,SIGNAL(clicked()),this,SLOT(ClickedRefresh()));
   connect(ui->btnH_0,SIGNAL(clicked()),this,SLOT(ClickedH0()));
   connect(ui->btnH_1,SIGNAL(clicked()),this,SLOT(ClickedH1()));
   connect(ui->btnH_2,SIGNAL(clicked()),this,SLOT(ClickedH2()));
   connect(ui->btnH_3,SIGNAL(clicked()),this,SLOT(ClickedH3()));
   connect(ui->btnH_4,SIGNAL(clicked()),this,SLOT(ClickedH4()));
   connect(ui->btnH_5,SIGNAL(clicked()),this,SLOT(ClickedH5()));
   connect(ui->btnH_6,SIGNAL(clicked()),this,SLOT(ClickedH6()));
   connect(ui->btnH_7,SIGNAL(clicked()),this,SLOT(ClickedH7()));
   connect(ui->btnH_8,SIGNAL(clicked()),this,SLOT(ClickedH8()));
}

void HelpSetDialog::ClickedClose(){
    this->close();
}

void HelpSetDialog::ClickedRefresh(){
    ui->webView->reload();
}
void HelpSetDialog::ClickedBack(){
    ui->webView->back();
}
void HelpSetDialog::ClickedForward(){
    ui->webView->forward();
}




void HelpSetDialog::ClickedHome(){
    QString pathHTML="";
    if(ui->cbxRD->isChecked())
       pathHTML = "http://emmodded.org/projects/sqlitetest/docs/html/resultdialog_8cpp.html";
    else
       pathHTML = QApplication::applicationDirPath()+"/docs/html/resultdialog_8cpp.html";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLiteTest - Doxygen Home :: " + pathHTML);
}

void HelpSetDialog::ClickedGit(){
    QString pathHTML  = "https://github.com/emmodded/SQLiteTest";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLiteTest - Git Repository :: " + pathHTML);
}


void HelpSetDialog::ClickedH0(){
    QString pathHTML  = "http://www.sqlite.org/atomiccommit.html";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Atomic Commit :: " + pathHTML);
}

void HelpSetDialog::ClickedH1(){
    QString pathHTML  = "http://www.sqlite.org/pragma.html#pragma_page_size";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Page Size Bytes :: " + pathHTML);
}

void HelpSetDialog::ClickedH2(){
    QString pathHTML  = "http://www.sqlite.org/pragma.html#pragma_cache_size";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Cache Size Bytes :: " + pathHTML);
}

void HelpSetDialog::ClickedH3(){
    QString pathHTML  = "http://www.sqlite.org/pragma.html#pragma_temp_store";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Temp Store Mode :: " + pathHTML);
}


void HelpSetDialog::ClickedH4(){
    QString pathHTML  = "http://www.sqlite.org/pragma.html#pragma_journal_mode";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Journal Mode :: " + pathHTML);
}

void HelpSetDialog::ClickedH5(){
    QString pathHTML  = "http://www.sqlite.org/pragma.html#pragma_locking_mode";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Locking Transaction Mode :: " + pathHTML);
}

void HelpSetDialog::ClickedH6(){
    QString pathHTML  = "http://www.sqlite.org/pragma.html#pragma_synchronous";
    ui->webView->load(QUrl(pathHTML));
    ui->viewerBox->setTitle("SQLite - Synchronous Transaction :: " + pathHTML);
}


void HelpSetDialog::ClickedH7(){
    QString strMSG="Use Stored Existing Database";
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strMSG,
    QMessageBox::Ok);
}


void HelpSetDialog::ClickedH8(){
    QString strMSG="Double buffer and double speed solutions \n implements for future scope";
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strMSG,
    QMessageBox::Ok);
}
