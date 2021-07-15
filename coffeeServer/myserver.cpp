#include <myserver.h>

myserver::myserver() {}

myserver::~myserver() {}

void myserver::startServer()
{
    if(this->listen(QHostAddress::Any,4444))
    {
        qDebug()<<"Listening";
    }
    else {
       qDebug()<<"Not listening";
    }
}

void myserver::incomingConnection(int socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

     qDebug()<<socketDescriptor<<" client connected";

     socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
     qDebug()<<"Sent client connect status - Y";

}

void myserver::sockReady()
{
    Data = socket->readAll();
    qDebug()<<"data:"<<Data;

    doc = QJsonDocument::fromJson(Data, &docError);
    //{"type":"Select", "params","order"}
    if (docError.errorString().toInt()==QJsonParseError::NoError)
    {
      if ((doc.object().value("type").toString() == "select") &&(doc.object().value("params").toString() == "order"))
      {
        QFile file;
        file.setFileName("C:\\Users\\DUTCH\\Documents\\coffee\\json.json");
        if (file.open(QIODevice::ReadOnly |QFile::Text))
        {
            QByteArray fromfile = file.readAll();
            //{"type":"resultselect","result":...}
            QByteArray itog = "{\"type\":\"resultselect\",\"result\":"+fromfile+"}";
qDebug()<<itog;
            socket->write(itog);
            socket->waitForBytesWritten(500);

        }
        file.close();
      }
      else {
          qDebug()<<"wrong query";

      }
    }
}

void myserver::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();

}
