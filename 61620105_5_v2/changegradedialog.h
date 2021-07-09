#ifndef CHANGEGRADEDIALOG_H
#define CHANGEGRADEDIALOG_H

#include <QDialog>
#include "student.h"
#include "course.h"

namespace Ui {
class ChangeGradeDialog;
}

class ChangeGradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeGradeDialog(int *grade, QWidget *parent = nullptr);
    ~ChangeGradeDialog();
    int *grade;

private slots:
    void on_cancel_box_clicked();

    void on_ok_button_clicked();

private:
    Ui::ChangeGradeDialog *ui;
};

#endif // CHANGEGRADEDIALOG_H
