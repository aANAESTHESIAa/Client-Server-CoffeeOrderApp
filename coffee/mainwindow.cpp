#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QTableView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisk()));
        socket->connectToHost("127.0.0.1",4444);

}

MainWindow::~MainWindow()
{
    delete ui;
}
int i=0;

void MainWindow::on_AddMainButton_clicked()
{


    file.setFileName("C:\\Users\\DUTCH\\Documents\\coffee\\json.json");




        if (file.open(QIODevice::WriteOnly))
        {
           QVariantMap map;
           if(ui->comboBox->currentIndex() > -1 )
           {
           map.insert("name",ui->comboBox->currentText());
           }
           else
           {
               QMessageBox::warning(nullptr,"Attention!","Please choose coffee type first!");
               return void();
           }


           if(ui->comboBox_2->currentIndex() > -1)
           {
           map.insert("topping",ui->comboBox_2->currentText());
           }
           else {
               QMessageBox::warning(nullptr,"Attention!","Please choose topping type first!");
               return void();
           }

           if(ui->comboBox_3->currentIndex() > -1)
           {
           map.insert("size",ui->comboBox_3->currentText());
           }
           else {
               QMessageBox::warning(nullptr,"Attention!","Please choose coffee size first!");
               return void();
           }

           QJsonObject jsonWriter = QJsonObject::fromVariantMap(map);

           QJsonArray docToWrite = doc.object().value("order").toArray();
           docToWrite.append(jsonWriter);
           doc.setArray(docToWrite);

          file.write("{\"order\":"+doc.toJson()+"}");
           file.close();
        }
        else {
          QMessageBox::information(nullptr,"Info","File open failure");
        }

        if (file.open(QIODevice::ReadOnly|QFile::Text))
        {
            doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
            file.close();

        if(docError.errorString().toInt()==QJsonParseError::NoError)
        {
            QStandardItemModel* model = new QStandardItemModel(nullptr);
            model->setHorizontalHeaderLabels(QStringList()<<"Coffee"<<"Topping"<<"Size");
          docArr = QJsonValue(doc.object().value("order")).toArray();
          for (int i=0; i<docArr.count();i++)
          {
             QStandardItem* item_col_1 = new QStandardItem(docArr.at(i).toObject().value("name").toString());
             QStandardItem* item_col_2 = new QStandardItem(docArr.at(i).toObject().value("topping").toString());
             QStandardItem* item_col_3 = new QStandardItem(docArr.at(i).toObject().value("size").toString());
             model->appendRow(QList<QStandardItem*>()<<item_col_1<<item_col_2<<item_col_3);

          }
           ui->tableView->setModel(model);
           ui->tableView->resizeColumnsToContents();

        }

    }
else
    {
        QMessageBox::information(nullptr,"Info","File open failure");
    }

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index==0)
     {
       QPixmap   pic("C:\\Users\\DUTCH\\Documents\\coffee\\0.png");
        ui->picLabel->setPixmap(pic);
        ui->picLabel->setScaledContents(true);
     }
       else if (index==1)
       {
        QPixmap pic("C:\\Users\\DUTCH\\Documents\\coffee\\1.png");
                   ui->picLabel->setPixmap(pic);
                   ui->picLabel->setScaledContents(true);
       }
    else if (index==2)
       {
        QPixmap pic("C:\\Users\\DUTCH\\Documents\\coffee\\2.png");
                   ui->picLabel->setPixmap(pic);
                   ui->picLabel->setScaledContents(true);
       }
    else if (index==3)
      {
        QPixmap pic("C:\\Users\\Dutch\\Documents\\coffee\\3.png");
                   ui->picLabel->setPixmap(pic);
                   ui->picLabel->setScaledContents(true);
      }
    else if (index==4)
      {
        QPixmap pic("C:\\Users\\Dutch\\Documents\\coffee\\4.png");
                   ui->picLabel->setPixmap(pic);
                   ui->picLabel->setScaledContents(true);
      }
    else if (index==5)
     {
        QPixmap pic("C:\\Users\\Dutch\\Documents\\coffee\\5.png");
                   ui->picLabel->setPixmap(pic);
                   ui->picLabel->setScaledContents(true);
     }
    else if (index==6)
     {
        QPixmap pic("C:\\Users\\Dutch\\Documents\\coffee\\6.png");
                  ui->picLabel->setPixmap(pic);
                  ui->picLabel->setScaledContents(true);
     }
}









void MainWindow::on_DelMainButton_clicked()
{
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
      file.close();
              }
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
        file.close(); }
    ui->tableView->setModel(model);



}

void MainWindow::on_FinishMainButton_clicked()
{
    if (ui->timeEdit->time() < QTime::currentTime())
    {
        QMessageBox::warning(this,"Achtung!","Sorry, but we can't turn back time! =( ");
               return void();
    }




    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        docf = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
        file.close(); }

    if (file.open(QIODevice::WriteOnly))
     {



         QJsonValue a=ui->timeEdit->time().toString();
         QJsonValue b = ui->checkBox->isChecked();





         QJsonObject prost =docf.object();
         prost.insert("time",a);
          prost.insert("TA",b);


         docf.setObject(prost);



        file.write(docf.toJson());
         file.close();

    }



    if(socket->isOpen())
    {
        socket->write("{\"type\":\"select\",\"params\":\"order\"}");
        socket->waitForBytesWritten(500);
    }
    else {
       QMessageBox::information(this,"info","connection failure");
    }
}
void MainWindow::sockDisk()
{
    socket->deleteLater();
}

void MainWindow::sockReady()
{
    if(socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();

        cdoc = QJsonDocument::fromJson(Data, &cdocEr);




        if (cdocEr.errorString().toInt()==QJsonParseError::NoError)
        {
            if ((cdoc.object().value("type").toString() == "connect") && (cdoc.object().value("status").toString() == "yes"))
            {
              QMessageBox::information(this,"Information","connection established");
            }
            else if (cdoc.object().value("type").toString() == "resultselect")
            {






         QJsonObject jsonObject = cdoc.object().value("result").toObject();



         QJsonArray jsonArray =jsonObject.value("order").toArray();





            bool TAT;

            TAT =QJsonValue(jsonObject.value("TA")).toBool();


            QString time;
            time = QJsonValue(jsonObject.value("time")).toString();





             for (int p=0; p<jsonArray.count(); p++)
             {

                 res=res+(jsonArray.at(p).toObject().value("name").toString())+ " with ";
                  res=res+(jsonArray.at(p).toObject().value("topping").toString())+ ". Size: ";
                   res=res+(jsonArray.at(p).toObject().value("size").toString())+".\n";

             }

            if (res==nullptr) {
                QMessageBox::warning(this,"wtf!","You haven't ordered anything!");
                        return void();
                }

             if (TAT==true)
             {
                 QMessageBox::information(this,"Thank you! Please take your order:",res+"at the cafe at "+time);

             }
             else
             {
               QMessageBox::information(this,"Thank you! We've booked a table for you! Your order:",res+"\n Please come by "+time);
             }





           }
            else
            {
              QMessageBox::information(this,"Information","connection failure");
            }

            res=nullptr;
        }
        else {
                 QMessageBox::information(this,"Information","parsing failure"+cdocEr.errorString());
             }
    }
}



