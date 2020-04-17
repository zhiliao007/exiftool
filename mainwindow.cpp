#include "mainwindow.h"
#include "ui_view.h"
#include "exifdecode.h"

#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>

const QString VERSION = "V0.1.2";
const char COLUMN_COUNT = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ExifTool " + VERSION + " by liwq");
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openProcess()));
    QObject::connect(ui->actionSave_as,SIGNAL(triggered()),this,SLOT(saveProcess()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showResultOnTable(QMap<QString, QString> result)
{
    //TODO: "Key" should be refined
    QMap<QString, QString> resultToShow = result;
    qDebug() << resultToShow.count();
    ui->tableWidget->setRowCount(resultToShow.count());
    ui->tableWidget->setColumnCount(COLUMN_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels({"ExifKey", "ExifValue"});
    char row_count = 0;
    for(QMap<QString, QString>::iterator iter = resultToShow.begin();
        iter != resultToShow.end(); iter++)
    {
        ui->tableWidget->setItem(row_count, 0,new QTableWidgetItem(iter.key()));
        ui->tableWidget->setItem(row_count, 1,new QTableWidgetItem(iter.value()));
        row_count++;
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //According to the space, automatically change the column width
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);   //According to the content, automatically change column width
}

void MainWindow::openProcess()
{
    QStringList openfile_list = QFileDialog::getOpenFileNames(this, "Choose File", "/home/liwq/code/exif-tools", "JPEG files(*.jpg *.JPG)");
    if(openfile_list.size() != 0)
    {
        if(openfile_list.size() > 1)
        {
            QMessageBox::warning(this, "Warning", "Only Support First Image !", QMessageBox::Ok);
        }
        qDebug() << openfile_list.at(0);
        exif_data = exifDecode::get_exif_data(openfile_list.at(0));
        showResultOnTable(exif_data);
    }
}

void MainWindow::saveProcess()
{
    //TODO: Wait for doing
    qDebug() << "TODO";
}
