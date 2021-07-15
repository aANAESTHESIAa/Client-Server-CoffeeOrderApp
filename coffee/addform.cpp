#include "addform.h"
#include "ui_addform.h"
#include "forjson.h"


addForm::addForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addForm)
{
    ui->setupUi(this);
}

addForm::~addForm()
{
    delete ui;
}

void addForm::on_AddButton_clicked()
{
  //  QStandardItemModel* model = new QStandardItemModel(nullptr);
  // model->setHorizontalHeaderLabels(QStringList()<<"name");
   // QStandardItem* col = new QStandardItem(ui->NameBox->currentText());
   // model->appendRow(col);
   //  ui->tableView->setModel(model);

}
