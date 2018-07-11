#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
   gmpad = new GamepadClient(ui->hostAdress->text(),ui->hostPort->text().toInt());
   QThread* thread = new QThread;

   gmpad->moveToThread(thread);

   connect(thread, SIGNAL(started()), gmpad, SLOT(connectToHost()));
   connect(thread,SIGNAL(finished()),gmpad, SLOT(threadFinished()));

   thread->start();
}
