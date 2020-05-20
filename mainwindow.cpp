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
    ui->tableWidget->setEditTriggers(QTableView::NoEditTriggers);     //No editing
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
        qDebug() << openfile_list.value(0);
        currfilename = openfile_list.value(0);
        exif_data = exifDecode::get_exif_data(currfilename);
        showResultOnTable(exif_data);
    }
}

void MainWindow::saveProcess()
{
    if(currfilename.isEmpty() == false)
    {
        QString savefile_name = QFileDialog::getSaveFileName(this, "Save File", currfilename.replace(".jpg", ".csv").replace(".JPG", ".csv"), "CSV files(*.csv)");
        qDebug() << savefile_name;
        int i = 0, j = 0;
        QString conTents ;
        if (savefile_name.isEmpty() == false)
        {
            QFile savefile(savefile_name);
            if(savefile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                for(i = 0; i < COLUMN_COUNT; i++)
                {
                    conTents += ui->tableWidget->horizontalHeaderItem(i)->text();
                    if (i != 1)
                        conTents += ',';
                }
                conTents += '\n';
                qDebug() <<ui->tableWidget->rowCount();
                for(j=0; j < ui->tableWidget->rowCount(); j++)
                {
                    conTents += '"' + ui->tableWidget->item(j, 0)->text() + '"';
                    conTents += ',';
                    conTents += '"' + ui->tableWidget->item(j, 1)->text() + '"';
                    conTents += '\n';
                }
                savefile.write(conTents.toUtf8());
            }
            QMessageBox::information(this, "info", "csv file saved successfully!");
            savefile.close();
        }
    }
}
