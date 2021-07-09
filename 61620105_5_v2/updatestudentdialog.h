#ifndef UPDATESTUDENTDIALOG_H
#define UPDATESTUDENTDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class UpdateStudentDialog;
}

class UpdateStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateStudentDialog(Student* student, MainWindow *parent = nullptr);
    ~UpdateStudentDialog();

    Student* student;
    MainWindow* mainwindow;


private slots:
    void on_cancel_button_clicked();

    void on_ok_button_clicked();

private:
    Ui::UpdateStudentDialog *ui;
};

#endif // UPDATESTUDENTDIALOG_H
