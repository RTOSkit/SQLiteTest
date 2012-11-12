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

#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog){
    ui->setupUi(this);
    cparent = (MainWindow*)parent;
    populateTable();
}

ResultDialog::~ResultDialog(){
    delete ui;
}


void ResultDialog::populateTable(){

    int nRecords = ((MainWindow*)cparent)->postTmpNrecords;
    int nTurns = ((MainWindow*)cparent)->resultTimes.count();//(((MainWindow*)cparent)->postTmpRunSeconds * 2) -1;
    bool fullSpeed = ((MainWindow*)cparent)->fullSpeed;


    QString operationTitle[2]={"RUN","SLEEP"};
    int mode=0;
    float totalRun=0;
    float totalSleep=0;
    float speedTot=0;

    ((MainWindow*)cparent)->resultTimes.count();

    //POPULATE OBJECT
    for(int j=0;j<nTurns;j++){
        ui->tableTL->insertRow(j);
        QTableWidgetItem *item;
        QString tmpS=operationTitle[mode];
        item =  new QTableWidgetItem(tmpS);
        ui->tableTL->setItem(j,0,item);
        speedTot =  ((MainWindow*)cparent)->resultTimes[j];
        if(!mode){
           // speedTot+=0.01;
            totalRun+=speedTot;
            mode=1;
            tmpS.sprintf("%5.3f",speedTot);
        }else{
          //  speedTot-=0.01;
            tmpS.sprintf("%5.3f",speedTot);
            totalSleep+=speedTot;
            mode=0;
        }
        item =  new QTableWidgetItem(tmpS);
        ui->tableTL->setItem(j,1,item);
    }

    QString tmpS;
    tmpS.sprintf("%5.0f",totalRun);
    QString totalRunStr = tmpS;
    tmpS.sprintf("%5.0f",totalSleep);
    QString totalSleepStr = tmpS;
    tmpS.sprintf("%5.0f",((fullSpeed)?totalRun:(((totalRun<1000)?1000:totalSleep)-totalSleep)));
    QString totalDRunStr = tmpS;
    tmpS.sprintf("%u",((MainWindow*)cparent)->RRLbytes);
    QString totalBytes=tmpS;
    tmpS.sprintf("%u",nRecords);
    QString totalRecords=tmpS;

    QString summary ="";
    summary.append("<center>");
    if(!((MainWindow*)cparent)->sqlite->sqlPreferences->useAtomicCommit)
        summary.append("<b>Atomic Commit</b><br />Disabled<br />");
    else
        summary.append("<b>Atomic Commit</b><br />Enabled<br />");
    summary.append("<b>Total Bytes:</b><br />" + totalBytes + " <br />");
    summary.append("<b>Total Records:</b><br />" + totalRecords + " <br />");
    summary.append("<b>Deducted Run Time in a second:</b><br />" + totalDRunStr + " ms <br />");
    summary.append("<b>Theoric Run Time:</b><br />" + totalRunStr + " ms<br />");
    summary.append("<b>Theoric Sleep Time:</b><br />" + totalSleepStr + " ms <br />");
    summary.append("</center>");
    ui->pteResult->appendHtml(summary);
}
