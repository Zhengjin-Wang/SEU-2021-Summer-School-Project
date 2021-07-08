#include "deldialog.h"
#include "ui_delstudentdialog.h"

DelDialog::DelDialog(bool* flag, const QString& hint, const QString& button1_text, const QString& button2_text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelStudentDialog)
{
    ui->setupUi(this);
    this->flag = flag;
    ui->label->setText(hint);
    ui->ok_button->setText(button1_text);
    ui->cancel_button->setText(button2_text);
}

DelDialog::~DelDialog()
{
    delete ui;
}

void DelDialog::on_cancel_button_clicked()
{   *flag = false;
    this->close();
}

void DelDialog::on_ok_button_clicked()
{
    *flag = true;
    this->close();
}
