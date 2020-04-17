#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMap<QString, QString> exif_data;

private slots:
    void openProcess();

    void saveProcess();

private:
    Ui::MainWindow *ui;
    void showResultOnTable(QMap<QString, QString> result);
};
#endif // MAINWINDOW_H
