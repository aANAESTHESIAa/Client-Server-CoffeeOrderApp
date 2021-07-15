#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDialog>
#include<QStandardItem>

namespace Ui {
class addForm;
}

class addForm : public QDialog
{
    Q_OBJECT

public:
    explicit addForm(QWidget *parent = 0);
    ~addForm();

private slots:
    void on_AddButton_clicked();

private:
    Ui::addForm *ui;
};

#endif // ADDFORM_H
