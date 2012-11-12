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

#ifndef HELPSETDIALOG_H
#define HELPSETDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "sqlite.h"


namespace Ui {
class HelpSetDialog;
}

class HelpSetDialog : public QDialog
{
    Q_OBJECT


    
public:
    explicit HelpSetDialog(bool firstCall, QWidget *parent = 0);
    ~HelpSetDialog();
    void closeEvent(QCloseEvent * event);

public slots:
    void ClickedHome();
    void ClickedClose();
    void ClickedH0();
    void ClickedH1();
    void ClickedH2();
    void ClickedH3();
    void ClickedH4();
    void ClickedH5();
    void ClickedH6();
    void ClickedH7();
    void ClickedH8();



private:
    Ui::HelpSetDialog *ui;
    SQLite *lSQLite;
    QWidget *cparent;
    void initListeners(void);
    void beforeClose(void);


};

#endif // HELPSETDIALOG_H
