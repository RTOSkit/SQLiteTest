#include "helper.h"
#include "ui_helper.h"

Helper::Helper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Helper)
{
    viewerForm = new ViewerForm(this);
    setCentralWidget(viewerForm);
    //ui->setupUi(this);
}

Helper::~Helper()
{
    delete ui;
}
