#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStandardItem>
#include <qpixmap.h>
#include<QPicture>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QJsonDocument doc;
        QJsonDocument docf;
    QJsonParseError docError;
      QStandardItemModel* model = new QStandardItemModel(nullptr);
    QJsonArray docArr;
    QFile file;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument cdoc;
    QJsonParseError cdocEr;
    QString res;
    QJsonDocument rdoc;
  public slots:
    void sockReady();
    void sockDisk();

private slots:




    void on_AddMainButton_clicked();


    void on_comboBox_currentIndexChanged(int index);

    void on_DelMainButton_clicked();

    void on_FinishMainButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
