#ifndef DELSTUDENTDIALOG_H
#define DELSTUDENTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class DelStudentDialog;
}

class DelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelDialog(bool* flag, const QString& hint = "您确定要删除吗？", const QString& button1_text = "确定", const QString& button2_text = "取消",QWidget *parent = nullptr);
    ~DelDialog();
    bool* flag;
private slots:
    void on_cancel_button_clicked();

    void on_ok_button_clicked();

private:
    Ui::DelStudentDialog *ui;
};

#endif // DELSTUDENTDIALOG_H
