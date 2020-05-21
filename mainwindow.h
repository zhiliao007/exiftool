#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMap>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openProcess();
    void saveProcess();
    void findProcess();
    void aboutProcess();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> exif_data;
    QString currfilename;
    QLineEdit *findLineEdit = NULL;

    void showResultOnTable(QMap<QString, QString> result);
};
#endif // MAINWINDOW_H
