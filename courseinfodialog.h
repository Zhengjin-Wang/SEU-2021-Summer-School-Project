#ifndef COURSEINFODIALOG_H
#define COURSEINFODIALOG_H

#include <QDialog>

namespace Ui {
class CourseInfoDialog;
}

class CourseInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseInfoDialog(QWidget *parent = nullptr);
    ~CourseInfoDialog();

private:
    Ui::CourseInfoDialog *ui;
};

#endif // COURSEINFODIALOG_H
