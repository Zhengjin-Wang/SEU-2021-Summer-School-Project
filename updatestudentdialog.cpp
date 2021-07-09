#include "updatestudentdialog.h"
#include "ui_updatestudentdialog.h"
#include <QPalette>

UpdateStudentDialog::UpdateStudentDialog(Student* student, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::UpdateStudentDialog)
{
    ui->setupUi(this);
    this->student = student;
    this->mainwindow = parent;

    ui->name->setText(student->getName());
    ui->_class->setText(student->getClass());
    ui->phone->setText(student->getPhone());
    ui->birth->setDate(student->getBirth());
    ui->address->setText(student->getAddress());

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->hint_label->setPalette(pe);
    
    this->setWindowTitle("修改"+student->getId()+student->getName()+"的信息");
}

UpdateStudentDialog::~UpdateStudentDialog()
{
    delete ui;
}

void UpdateStudentDialog::on_cancel_button_clicked()
{
    this->close();
}

void UpdateStudentDialog::on_ok_button_clicked()
{
    if(!ui->name->text().size()||!ui->_class->text().size()||!ui->phone->text().size()||!ui->address->text().size()){
        ui->hint_label->setText("请确保信息填写完整");
        return;
    }
    if(ui->name->text().contains(' ')||ui->_class->text().contains(' ')||ui->phone->text().contains(' ')||ui->address->text().contains(' ')){
        ui->hint_label->setText("输入信息不能带有空格");
        return;
    }

    student->setName(ui->name->text());
    student->setClass(ui->_class->text());
    student->setPhone(ui->phone->text());
    student->setBirth(ui->birth->date());
    student->setAddress(ui->name->text());
    this->close();
}
