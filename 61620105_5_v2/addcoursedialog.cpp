#include "addcoursedialog.h"
#include "ui_addcoursedialog.h"
#include<QString>
#include<QMessageBox>
#include<QDebug>

AddCourseDialog::AddCourseDialog(Student* student, MainWindow *parent, QString* course_id,  QList<QString> *valid_course_list) :
    QDialog(nullptr),
    ui(new Ui::AddCourseDialog)
{
    ui->setupUi(this);
    this->course_id = course_id;
    this->student = student;
    this->mainwindow = parent;
    this->valid_course_list = valid_course_list;

    //将课程信息录入combobox，只有未选的课出现在comboBox中

    for(QString& course_name : *valid_course_list){

        ui->course_comboBox->addItem(course_name);
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
