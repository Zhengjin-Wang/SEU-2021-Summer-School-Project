#ifndef COURSEINFODIALOG_H
#define COURSEINFODIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "course.h"

namespace Ui {
class CourseInfoDialog;
}

class CourseInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseInfoDialog(Course* course, QWidget *parent);
    ~CourseInfoDialog();

    Course *course;
    MainWindow *mainwindow;

    void init();


private:
    Ui::CourseInfoDialog *ui;
};

#endif // COURSEINFODIALOG_H
