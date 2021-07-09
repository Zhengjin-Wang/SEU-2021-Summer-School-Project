#include "changegradedialog.h"
#include "ui_changegradedialog.h"

ChangeGradeDialog::ChangeGradeDialog(int *grade, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeGradeDialog)
{
    ui->setupUi(this);
    this->grade = grade;
    ui->grade_box->setValue(*grade);
}

ChangeGradeDialog::~ChangeGradeDialog()
{
    delete ui;
}

void ChangeGradeDialog::on_cancel_box_clicked()
{
    this->close();
}

void ChangeGradeDialog::on_ok_button_clicked()
{
    *grade = ui->grade_box->value();
    this->close();
}
