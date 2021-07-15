#ifndef FORJSON_H
#define FORJSON_H
#include "forjson.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include "addform.h"


class item
{
public:
    Item(QJsonObject JSobj);
    QJsonObject toJsonObject();
    void setcoffeN(QString CN) { coffeeN = CN; }
    void setcoffeT(QString CT) { coffeeT = CT; }
    void setcoffeS(QString CS) { coffeeS = CS; }
private:
    QString coffeeN;
    QString coffeeT;
    QString coffeeS;


};
class order
{
public:
    order(QJsonObject JSobj);
     QJsonObject toJsonObject();
private:

   int number;
   QList<item> items;
   bool takeaway;
   QString time;

};

#endif // FORJSON_H
