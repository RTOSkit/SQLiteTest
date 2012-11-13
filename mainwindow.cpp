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

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){    
    ui->setupUi(this);
    createActions();
    createMenus();
    initVectors();
    initListeners();
    muteEvent=false;
    ClickedClear();
    sqlite = new SQLite();
    openSet(true);
    sqlite->startDriver();
}

MainWindow::~MainWindow(){
    delete ui;
    sqlite->dbFlush();
}






/**
 * @section MainWindow config
 *
 */
void MainWindow::createActions(){
    openAct = new QAction(tr("&Set..."), this);
    openAct->setStatusTip(tr("Open HelpSet Dialog"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setStatusTip(tr("Exit the application"));
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}
void MainWindow::initVectors(void){

    int idx=0;
    sbxLenghtVector[idx]= ui->sbxFFG_0;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_0;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_0;
    txtTextContentVector[idx] = ui->txtFFG_0;
    idx=1;
    sbxLenghtVector[idx]= ui->sbxFFG_1;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_1;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_1;
    txtTextContentVector[idx] = ui->txtFFG_1;
    idx=2;
    sbxLenghtVector[idx]= ui->sbxFFG_2;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_2;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_2;
    txtTextContentVector[idx] = ui->txtFFG_2;
    idx=3;
    sbxLenghtVector[idx]= ui->sbxFFG_3;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_3;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_3;
    txtTextContentVector[idx] = ui->txtFFG_3;
    idx=4;
    sbxLenghtVector[idx]= ui->sbxFFG_4;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_4;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_4;
    txtTextContentVector[idx] = ui->txtFFG_4;
    idx=5;
    sbxLenghtVector[idx]= ui->sbxFFG_5;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_5;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_5;
    txtTextContentVector[idx] = ui->txtFFG_5;
    idx=6;
    sbxLenghtVector[idx]= ui->sbxFFG_6;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_6;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_6;
    txtTextContentVector[idx] = ui->txtFFG_6;
    idx=7;
    sbxLenghtVector[idx]= ui->sbxFFG_7;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_7;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_7;
    txtTextContentVector[idx] = ui->txtFFG_7;
    idx=8;
    sbxLenghtVector[idx]= ui->sbxFFG_8;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_8;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_8;
    txtTextContentVector[idx] = ui->txtFFG_8;
    idx=9;
    sbxLenghtVector[idx]= ui->sbxFFG_9;
    cbxTextFieldVector[idx] = ui->cbxFFG_TEXT_9;
    cbxRandomContentVector[idx] = ui->cbxFFG_RANDOM_9;
    txtTextContentVector[idx] = ui->txtFFG_9;

}
void MainWindow::initListeners(void){
   connect(ui->dialEPS, SIGNAL(valueChanged(int)), this, SLOT(setValueEPS(int)));
   connect(ui->dialST, SIGNAL(valueChanged(int)), this, SLOT(setValueST(int)));

   connect(ui->btnClear,SIGNAL(clicked()),this,SLOT(ClickedClear()));
   connect(ui->btnMake,SIGNAL(clicked()),this,SLOT(ClickedMake()));
   connect(ui->btnTESTINSERT,SIGNAL(clicked()),this,SLOT(ClickedTESTINSERT()));
   connect(ui->btnTESTUPDATE,SIGNAL(clicked()),this,SLOT(ClickedTESTUPDATE()));
   connect(ui->btnTESTDELETE,SIGNAL(clicked()),this,SLOT(ClickedTESTDELETE()));
   connect(ui->btnTESTSELECT,SIGNAL(clicked()),this,SLOT(ClickedTESTSELECT()));

   connect(ui->cbxFFG_TEXT_0,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_1,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_2,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_3,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_4,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_5,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_6,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_7,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_8,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));
   connect(ui->cbxFFG_TEXT_9,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldType(int)));

   connect(ui->cbxFFG_RANDOM_0,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_1,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_2,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_3,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_4,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_5,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_6,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_7,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_8,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
   connect(ui->cbxFFG_RANDOM_9,SIGNAL(stateChanged(int)),this,SLOT(ChangeFFGfieldContent(int)));
}







/**
 * @section MainWindow post Slots
 *
 */
void MainWindow::processClearALL(){
    muteEvent=true;
    ui->cbxFFG_TEXT_0->setChecked(false);
    ui->cbxFFG_TEXT_1->setChecked(false);
    ui->cbxFFG_TEXT_2->setChecked(false);
    ui->cbxFFG_TEXT_3->setChecked(false);
    ui->cbxFFG_TEXT_4->setChecked(false);
    ui->cbxFFG_TEXT_5->setChecked(false);
    ui->cbxFFG_TEXT_6->setChecked(false);
    ui->cbxFFG_TEXT_7->setChecked(false);
    ui->cbxFFG_TEXT_8->setChecked(false);

    ui->cbxFFG_RANDOM_0->setChecked(true);
    ui->cbxFFG_RANDOM_1->setChecked(true);
    ui->cbxFFG_RANDOM_2->setChecked(true);
    ui->cbxFFG_RANDOM_3->setChecked(true);
    ui->cbxFFG_RANDOM_4->setChecked(true);
    ui->cbxFFG_RANDOM_5->setChecked(true);
    ui->cbxFFG_RANDOM_6->setChecked(true);
    ui->cbxFFG_RANDOM_7->setChecked(true);
    ui->cbxFFG_RANDOM_8->setChecked(true);
    ui->cbxFFG_RANDOM_9->setChecked(true);
    muteEvent=false;

    ChangeFFGfieldType(0);
    ChangeFFGfieldContent(0);

    int nRows = ui->tableRRL->rowCount();
    for(int j=0;j<nRows;j++){
        ui->tableRRL->removeRow(0);
    }
    ui->groupBoxRRL->setTitle(RRL_TITLE);

    nRows = ui->tableDRL->rowCount();
    for(int j=0;j<nRows;j++){
        ui->tableDRL->removeRow(0);
    }
    ui->groupBoxDRL->setTitle(DRL_TITLE);

    isSelect=false;
    RRLbytes = DRLbytes = 0;
    ui->tbMain->setCurrentIndex(0);
}

void MainWindow::processMakeRRL(){

    isSelect=false;
    int nRecords = ui->dialEPS->value();

    //CLEAR OBJECT
    int nRows = ui->tableRRL->rowCount();
    for(int j=0;j<nRows;j++){
        ui->tableRRL->removeRow(0);
    }

    nRows = ui->tableDRL->rowCount();
    for(int j=0;j<nRows;j++){
        ui->tableDRL->removeRow(0);
    }
    ui->groupBoxDRL->setTitle(DRL_TITLE);
    RRLbytes = DRLbytes = 0;


    //POPULATE OBJECT
    for(int j=0;j<nRecords;j++){
        ui->tableRRL->insertRow(j);
        for(int i=0;i<FIX_NR_FIELDS;i++){
            QTableWidgetItem *item;
            QString tmpS="";
            if(cbxRandomContentVector[i]->isChecked()){
                tmpS = randomFixString(
                       ((cbxTextFieldVector[i]->isChecked())?
                         TEXT_FIELD_SIZE:
                         sbxLenghtVector[i]->value()));
            }else{
                tmpS = (txtTextContentVector[i]->text().length()>=1)?txtTextContentVector[i]->text():" ";
            }
            RRLbytes += tmpS.length();
            item = new QTableWidgetItem(tmpS);
            ui->tableRRL->setItem(j,i,item);
        }
    }

    QString strRRLbytes="";
    float speedRequired = RRLbytes / 8;
    strRRLbytes.sprintf(": %u Bytes, Speed request %9.1fkbits/s",RRLbytes,speedRequired);
    ui->groupBoxRRL->setTitle(RRL_TITLE+strRRLbytes);
}

void MainWindow::processTestInsert(){
    int nRows = ui->tableRRL->rowCount();
    for(int j=0;j<nRows;j++){
        dataDB[j].append(j+"");
        for(int i=0;i<FIX_NR_FIELDS;i++){
            QTableWidgetItem *item = ui->tableRRL->item(0,i);
            QString itemStr = item->text();
            dataDB[j].append(itemStr);
        }
        ui->tableRRL->removeRow(0);
    }

    if(nRows){
        isQueryError=false;
        tmpNrecords = nRows;
        postTmpNrecords = tmpNrecords;
        ui->groupBoxRRL->setTitle(RRL_TITLE);
        QString msg = "Insert Sentence is Ready! \nDo you want run in fullSpeed Mode?";
        if(QMessageBox::question(0, qApp->tr("SQLiteTest"),msg,
                                    QMessageBox::Ok,QMessageBox::No)==QMessageBox::Ok){
            fullSpeed=true;
            insertInvokeFullSpeed();
        }else{
            fullSpeed=false;
            startRunTimer(SLOT(runTimerInsertEvent()));
        }

    }else{
        QMessageBox::warning(0, qApp->tr("SQLiteTest"),
        qApp->tr("Ram Records List - is Empty"),
        QMessageBox::Ok);
    }
}

void MainWindow::processTestUpdate(){
    int nRows = ui->tableDRL->rowCount();
    for(int j=0;j<nRows;j++){        
        for(int i=0;i<FIX_NR_FIELDS;i++){
            QTableWidgetItem *item = ui->tableDRL->item(0,i);
            QString itemStr = item->text();
            dataDB[j].append(itemStr);
        }
        ui->tableDRL->removeRow(0);
    }

    if(nRows){
        isQueryError=false;
        tmpNrecords = nRows;
        postTmpNrecords = tmpNrecords;
        ui->groupBoxDRL->setTitle(DRL_TITLE);
        QString msg = "Update Sentence is Ready! \nDo you want run in fullSpeed Mode?";
        if(QMessageBox::question(0, qApp->tr("SQLiteTest"),msg,
                                    QMessageBox::Ok,QMessageBox::No)==QMessageBox::Ok){
            fullSpeed=true;
            updateInvokeFullSpeed();
        }else{
            fullSpeed=false;
            startRunTimer(SLOT(runTimerUpdateEvent()));
        }

    }else{
        QMessageBox::warning(0, qApp->tr("SQLiteTest"),
             qApp->tr("Data Records List - is Empty!\n Please run a 'Select Test' first."),
        QMessageBox::Ok);
    }


}

void MainWindow::processTestSelect(){
    int nRows = ui->tableRRL->rowCount();
    if(nRows){
        for(int j=0;j<nRows;j++){
            ui->tableRRL->removeRow(0);
        }
    }else{
       nRows = ui->dialEPS->value();
    }
    isQueryError=false;
    tmpNrecords = nRows;
    postTmpNrecords = tmpNrecords;
    ui->groupBoxRRL->setTitle(RRL_TITLE);
    QString msg = "Select Sentence is Ready! \nDo you want run in fullSpeed Mode?";
    if(QMessageBox::question(0, qApp->tr("SQLiteTest"),msg,
                                QMessageBox::Ok,QMessageBox::No)==QMessageBox::Ok){
        fullSpeed=true;
        selectInvokeFullSpeed();
    }else{
        fullSpeed=false;
        startRunTimer(SLOT(runTimerSelectEvent()));
    }
}

void MainWindow::processTestDelete(){
    int nRows = ui->tableRRL->rowCount();
    if(nRows){
        for(int j=0;j<nRows;j++){
            ui->tableRRL->removeRow(0);
        }
    }else{
       nRows = ui->dialEPS->value();
    }
    isQueryError=false;
    tmpNrecords = nRows;
    postTmpNrecords = tmpNrecords;
    ui->groupBoxRRL->setTitle(RRL_TITLE);
    QString msg = "Delete Sentence is Ready! \nDo you want run in fullSpeed Mode?";
    if(QMessageBox::question(0, qApp->tr("SQLiteTest"),msg,
                                QMessageBox::Ok,QMessageBox::No)==QMessageBox::Ok){
        fullSpeed=true;
        deleteInvokeFullSpeed();
    }else{
        fullSpeed=false;
        startRunTimer(SLOT(runTimerDeleteEvent()));
    }
}



/**
 * @section MainWindow SQL invokes Methods
 *
 */
void MainWindow::insertInvoke(void){
    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    tmpNrecords--;
    if(tmpNrecords<0){
      isBusy=false;
      stopProcess();
      return;
    }
    ctrlTimer.start();
    this->sqlite->insertDBRecord(dataDB[tmpNrecords]);
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    resultTimesIdx++;


    if(tmpNrecords==0){
       isBusy=false;
       stopProcess();
    }
}


void MainWindow::insertInvokeFullSpeed(void){

    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    this->ui->centralWidget->setEnabled(false);
    resultTimes.clear();
    ctrlTimer.start();
    this->sqlite->dbOpen();
    for(int i=0;i<tmpNrecords;i++){
       this->sqlite->insertDBRecord(dataDB[i]);
    }
    this->sqlite->dbClose();
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    this->ui->centralWidget->setEnabled(true);
    openResult();

    /*DEBUG
    QString strCtrlMS="";
    strCtrlMS.sprintf("Total Insert in %u MS",ctrlMS);
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strCtrlMS,
    QMessageBox::Ok);
    */
}


void MainWindow::updateInvoke(void){
    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    tmpNrecords--;
    if(tmpNrecords<0){
      isBusy=false;
      stopProcess();
      return;
    }
    ctrlTimer.start();
    this->sqlite->updateDBRecord(dataDB[tmpNrecords]);
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    resultTimesIdx++;


    if(tmpNrecords==0){
       isBusy=false;
       stopProcess();
    }
}


void MainWindow::updateInvokeFullSpeed(void){

    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    this->ui->centralWidget->setEnabled(false);
    resultTimes.clear();
    ctrlTimer.start();
    this->sqlite->dbOpen();
    for(int i=0;i<tmpNrecords;i++){
       this->sqlite->updateDBRecord(dataDB[i]);
    }
    this->sqlite->dbClose();
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    this->ui->centralWidget->setEnabled(true);
    openResult();

    /*DEBUG
    QString strCtrlMS="";
    strCtrlMS.sprintf("Total Insert in %u MS",ctrlMS);
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strCtrlMS,
    QMessageBox::Ok);
    */
}


void MainWindow::selectInvoke(void){
    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    tmpNrecords--;
    if(tmpNrecords<0){
      isBusy=false;
      isSelect=true;
      stopProcess();
      return;
    }
    QString str ="";
    ctrlTimer.start();
    dataDB[tmpNrecords] = this->sqlite->selectDBRecord(str.setNum(tmpNrecords));
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    resultTimesIdx++;


    if(tmpNrecords==0){
       isBusy=false;
       isSelect=true;
       stopProcess();
    }
}


void MainWindow::selectInvokeFullSpeed(void){

    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    this->ui->centralWidget->setEnabled(false);
    resultTimes.clear();
    ctrlTimer.start();
    this->sqlite->dbOpen();
    QString str ="";
    for(int i=0;i<tmpNrecords;i++){       
        dataDB[i] = this->sqlite->selectDBRecord(str.setNum(i));
    }
    this->sqlite->dbClose();
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    this->ui->centralWidget->setEnabled(true);       
    populateDRL();
    ui->tbMain->setCurrentIndex(1);
    openResult();

    /*DEBUG
    QString strCtrlMS="";
    strCtrlMS.sprintf("Total Insert in %u MS",ctrlMS);
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strCtrlMS,
    QMessageBox::Ok);
    */
}


void MainWindow::deleteInvoke(void){
    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    tmpNrecords--;
    if(tmpNrecords<0){
      isBusy=false;
      stopProcess();
      return;
    }
    ctrlTimer.start();
    if(!this->sqlite->deleteDBRecord()){
        stopProcess();
        isQueryError=true;
        queryErrorMsg.sprintf(" in %u record.",postTmpNrecords - tmpNrecords);
        tmpNrecords=0;
    }
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    resultTimesIdx++;


    if(tmpNrecords==0){
       isBusy=false;
       stopProcess();
    }
}


void MainWindow::deleteInvokeFullSpeed(void){

    QElapsedTimer ctrlTimer;
    int ctrlMS=0;
    this->ui->centralWidget->setEnabled(false);
    resultTimes.clear();
    ctrlTimer.start();
    this->sqlite->dbOpen();
    for(int i=0;i<tmpNrecords;i++){
       if(!this->sqlite->deleteDBRecord()){
            isQueryError=true;
            queryErrorMsg.sprintf(" in %u record.",postTmpNrecords - tmpNrecords);
            break;
       }
    }
    this->sqlite->dbClose();
    ctrlMS= ctrlTimer.elapsed();
    lastTime = ctrlMS;
    resultTimes.append(ctrlMS);
    this->ui->centralWidget->setEnabled(true);
    openResult();

    /*DEBUG
    QString strCtrlMS="";
    strCtrlMS.sprintf("Total Insert in %u MS",ctrlMS);
    QMessageBox::information(0, qApp->tr("SQLiteTest"),
    strCtrlMS,
    QMessageBox::Ok);
    */
}



/**
 * @section MainWindow code methods
 *
 */
void MainWindow::populateDRL(){
    int nRecords = ui->dialEPS->value();

    //CLEAR OBJECT
    int nRows = ui->tableDRL->rowCount();
    for(int j=0;j<nRows;j++){
        ui->tableDRL->removeRow(0);
    }
    DRLbytes=0;

    //POPULATE OBJECT
    for(int j=0;j<nRecords;j++){
        ui->tableDRL->insertRow(j);
        for(int i=0;i<FIX_NR_FIELDS;i++){
            if(dataDB[j].length()!=10){
                isQueryError=true;
                queryErrorMsg.sprintf(" only %u records found.",postTmpNrecords - tmpNrecords);
                goto lPOPULATEDRL_EXIT;
            }
            QTableWidgetItem *item;
            QString tmpS="";
            tmpS = dataDB[j][i];
            DRLbytes += tmpS.length();
            item = new QTableWidgetItem(tmpS);
            ui->tableDRL->setItem(j,i,item);
        }
    }

lPOPULATEDRL_EXIT:
    QString strDRLbytes="";
    float speedRequired = DRLbytes / 8;
    strDRLbytes.sprintf(": %u Bytes, Speed %9.1fkbits/s",DRLbytes,speedRequired);
    ui->groupBoxDRL->setTitle(DRL_TITLE+strDRLbytes);
}



/**
 * @section MainWindow Tests with timer flow
 *
 */
void MainWindow::startRunTimer(const char* runStepper){
    this->runStepper = runStepper;
    runTimer = new QTimer();
    connect(runTimer,SIGNAL(timeout()),this,runStepper);
    ui->centralWidget->setEnabled(false);
    int tI= floor(1000 / ui->lcdNumberEPS->value());
    tmpRunSeconds = ui->lcdNumberST->value();
    postTmpRunSeconds = tmpRunSeconds;
    sleepTime = tI;
    resultTimesIdx=0;
    isSelect=false;
    resultTimes.clear();
    this->sqlite->dbOpen();
    //timeout timer
    mainTimer = startTimer(1000);
    //steps timer
    runTimer->start(tI);
}

void MainWindow::stopProcess(){
    if(!isBusy){
        runTimer->stop();
        disconnect(runTimer,SIGNAL(timeout()),this,this->runStepper);
        killTimer(mainTimer);
        this->sqlite->dbClose();
        this->ui->centralWidget->setEnabled(true);        
        if(isSelect){
            populateDRL();
            ui->tbMain->setCurrentIndex(1);
        }
        openResult();
    }
}











/**
 * @section MainWindow Code Slots
 *
 */
void MainWindow::timerEvent(QTimerEvent *){
    if(!tmpRunSeconds){
        QString strMSG="Operation not completed due to timeout!";
        QMessageBox::warning(0, qApp->tr("SQLiteTest"),strMSG,QMessageBox::Ok);
        stopProcess();
    }else{
       tmpRunSeconds--;
    }
}
void MainWindow::runTimerInsertEvent(){
    if(!isBusy){
        isBusy=true;
        if(resultTimesIdx){
            resultTimes.append(sleepTime - lastTime);
            resultTimesIdx++;
        }
        insertInvoke();       
        isBusy=false;
    }
}
void MainWindow::runTimerSelectEvent(){
    if(!isBusy){
        isBusy=true;
        if(resultTimesIdx){
            resultTimes.append(sleepTime - lastTime);
            resultTimesIdx++;
        }
        selectInvoke();
        isBusy=false;
    }
}
void MainWindow::runTimerDeleteEvent(){
    if(!isBusy){
        isBusy=true;
        if(resultTimesIdx){
            resultTimes.append(sleepTime - lastTime);
            resultTimesIdx++;
        }
        deleteInvoke();
        isBusy=false;
    }
}
void MainWindow::runTimerUpdateEvent(){
    if(!isBusy){
        isBusy=true;
        if(resultTimesIdx){
            resultTimes.append(sleepTime - lastTime);
            resultTimesIdx++;
        }
        updateInvoke();
        isBusy=false;
    }
}













/**
 * @section MainWindow User Slots
 *
 */
void MainWindow::ChangeFFGfieldType(int){

    if(!muteEvent){
        ui->sbxFFG_0->setEnabled(!ui->cbxFFG_TEXT_0->isChecked());
        ui->sbxFFG_1->setEnabled(!ui->cbxFFG_TEXT_1->isChecked());
        ui->sbxFFG_2->setEnabled(!ui->cbxFFG_TEXT_2->isChecked());
        ui->sbxFFG_3->setEnabled(!ui->cbxFFG_TEXT_3->isChecked());
        ui->sbxFFG_4->setEnabled(!ui->cbxFFG_TEXT_4->isChecked());
        ui->sbxFFG_5->setEnabled(!ui->cbxFFG_TEXT_5->isChecked());
        ui->sbxFFG_6->setEnabled(!ui->cbxFFG_TEXT_6->isChecked());
        ui->sbxFFG_7->setEnabled(!ui->cbxFFG_TEXT_7->isChecked());
        ui->sbxFFG_8->setEnabled(!ui->cbxFFG_TEXT_8->isChecked());
        ui->sbxFFG_9->setEnabled(!ui->cbxFFG_TEXT_9->isChecked());
    }

}
void MainWindow::ChangeFFGfieldContent(int){

    if(!muteEvent){
        ui->txtFFG_0->setEnabled(!ui->cbxFFG_RANDOM_0->isChecked());
        ui->txtFFG_1->setEnabled(!ui->cbxFFG_RANDOM_1->isChecked());
        ui->txtFFG_2->setEnabled(!ui->cbxFFG_RANDOM_2->isChecked());
        ui->txtFFG_3->setEnabled(!ui->cbxFFG_RANDOM_3->isChecked());
        ui->txtFFG_4->setEnabled(!ui->cbxFFG_RANDOM_4->isChecked());
        ui->txtFFG_5->setEnabled(!ui->cbxFFG_RANDOM_5->isChecked());
        ui->txtFFG_6->setEnabled(!ui->cbxFFG_RANDOM_6->isChecked());
        ui->txtFFG_7->setEnabled(!ui->cbxFFG_RANDOM_7->isChecked());
        ui->txtFFG_8->setEnabled(!ui->cbxFFG_RANDOM_8->isChecked());
        ui->txtFFG_9->setEnabled(!ui->cbxFFG_RANDOM_9->isChecked());
     }
}
void MainWindow::setValueEPS(int value){
    ui->lcdNumberEPS->display(value);
}
void MainWindow::setValueST(int value){
    ui->lcdNumberST->display(value);
}
void MainWindow::ClickedClear(){
    processClearALL();
}
void MainWindow::ClickedMake(){
    processMakeRRL();
}
void MainWindow::about(){
    AboutDialog *aboutDialog = new AboutDialog();
    aboutDialog->show();
}
void MainWindow::open(){
    openSet(false);
}
void MainWindow::openSet(bool firstCall){
    HelpSetDialog *helpSetDialog = new HelpSetDialog(firstCall,this);
    helpSetDialog->show();
}
void MainWindow::openResult(){
    ResultDialog *resultDialog = new ResultDialog(this);
    resultDialog->show();
}
void MainWindow::ClickedTESTINSERT(){
    processTestInsert();
}
void MainWindow::ClickedTESTUPDATE(){
    processTestUpdate();
}
void MainWindow::ClickedTESTDELETE(){
    processTestDelete();
}
void MainWindow::ClickedTESTSELECT(){
    processTestSelect();
}





 /**
  * @section Helpers
  *
  */
QString MainWindow::randomFixString(int lenght){
    QString ABC[] = {"QWERTYUIOPASDFGHJKLZXCVBNM",
                     "qwertyuiopasdfghjklzxcvbnm"};
    QString out="";
    for(int i=0;i<lenght;i++){
        int cs= qrand() % 2,ls= qrand() % 25;
        out+=ABC[cs].at(ls).toAscii();
    }
    return out;
}


