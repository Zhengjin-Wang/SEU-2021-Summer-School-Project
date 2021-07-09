#ifndef LOGINTERFACE_H
#define LOGINTERFACE_H

#include <QMainWindow>
#include<QString>
#include<QHash>

namespace Ui {
class LogInterface;
}

class LogInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogInterface(QWidget *parent = nullptr);
    ~LogInterface();

    bool logAdmit(QString user,QString password);

    QApplication* application_ptr;

private slots:
    void on_exit_button_clicked();

    void on_login_button_clicked();

private:
    Ui::LogInterface *ui;
    QHash<QString,QString> user_list;

    void loadFile();
};

#endif // LOGINTERFACE_H
