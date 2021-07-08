#include "addcoursedialog.h"
#include "ui_addcoursedialog.h"
#include<QString>
#include<QMessageBox>
#include<QDebug>

AddCourseDialog::AddCourseDialog(Student* student, MainWindow *parent, QString* course_id) :
    QDialog(parent),
    ui(new Ui::AddCourseDialog)
{
    ui->setupUi(this);
    this->course_id = course_id;
    this->student = student;
    this->mainwindow = parent;

    //将课程信息录入combobox，只有未选的课出现在comboBox中
    QList<QString> course_list =  student->course_list.keys(); //这是课程id

    for(QString& course_name : mainwindow->course_map.keys()){
        if(!course_list.contains(mainwindow->course_map[course_name])){
            if(empty) empty = false;
            ui->course_comboBox->addItem(course_name);
        }
    }

    if(empty){
        QMessageBox::information(mainwindow,"提示","该学生已经没有可添加的课程");
    }
}

AddCourseDialog::~AddCourseDialog()
{
    delete ui;
}

void AddCourseDialog::on_cancel_button_clicked()
{
    this->close();
}

void AddCourseDialog::on_ok_button_clicked()
{
    //在底层加入数据
    //学生的选课清单加入课程的同时，也要在该课中加入该学生
    *course_id = mainwindow->course_map[ui->course_comboBox->currentText()];
    student->addCourse(*course_id,ui->grade_spinBox->value());
    mainwindow->all_course_list[*course_id]->addStudent(student);

    this->close();
}
