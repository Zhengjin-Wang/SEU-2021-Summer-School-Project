#ifndef STUDENTINFODIALOG_H
#define STUDENTINFODIALOG_H

#include <QDialog>
#include "student.h"
#include "mainwindow.h"
#include "addcoursedialog.h"

namespace Ui {
class StudentInfoDialog;
}

class StudentInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInfoDialog(Student* student, MainWindow* parent);
    ~StudentInfoDialog();

    Student* student;
    MainWindow* mainwindow;

    //修改课程信息时，应当在相应课程列表也增删该学生信息
    void addCourseInView(const QString& course_id, int init_index = -1); //需要一个addDialog

private slots:


    void on_add_button_clicked();

    void on_del_button_clicked();

    void on_change_button_clicked();

private:
    Ui::StudentInfoDialog *ui;
};

#endif // STUDENTINFODIALOG_H
