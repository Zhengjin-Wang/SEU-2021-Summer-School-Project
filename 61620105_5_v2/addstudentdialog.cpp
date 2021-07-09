#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include "mainwindow.h"
#include<QDebug>
#include<QPushButton>
#include<QString>
#include<QDate>
#include<QList>
#include<QPalette>

AddStudentDialog::AddStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);

    //设置提示label的颜色
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->hint_label->setPalette(pe);
}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}

void AddStudentDialog::on_pushButton_clicked()
{
    MainWindow* mainwindow = dynamic_cast<MainWindow*>(this->parent());
    //若遇到学号重复或手机等格式错误，应提示
    if(!ui->id->text().size()||!ui->name->text().size()||!ui->_class->text().size()||!ui->phone->text().size()||!ui->address->text().size()){
        ui->hint_label->setText("请确保信息填写完整");
        return;
    }
    if(mainwindow->all_student_list.find(ui->id->text()) != mainwindow->all_student_list.end()){
        ui->hint_label->setText("该学生的信息已经录入!");
        return;
    }
    if(ui->id->text().contains(' ')||ui->name->text().contains(' ')||ui->_class->text().contains(' ')||ui->phone->text().contains(' ')||ui->address->text().contains(' ')){
        ui->hint_label->setText("输入信息不能带有空格");
        return;
    }

    mainwindow->addStudent(ui->id->text(),new Student(ui->id->text(),ui->name->text(),ui->_class->text(),ui->phone->text(),ui->birth->date(),ui->address->text()));
    this->close();
}

void AddStudentDialog::on_pushButton_2_clicked()
{
    this->close();
}
