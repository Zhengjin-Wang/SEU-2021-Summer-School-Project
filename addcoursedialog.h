#ifndef ADDCOURSEDIALOG_H
#define ADDCOURSEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AddCourseDialog;
}

class AddCourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourseDialog(Student *student, MainWindow *parent, QString *course_id);
    ~AddCourseDialog();

    Student* student;
    MainWindow* mainwindow;
    QString* course_id;
    bool empty = true;

private slots:
    void on_cancel_button_clicked();

    void on_ok_button_clicked();

private:
    Ui::AddCourseDialog *ui;
};

#endif // ADDCOURSEDIALOG_H
