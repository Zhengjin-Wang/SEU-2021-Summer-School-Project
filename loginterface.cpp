#include "loginterface.h"
#include "ui_loginterface.h"
#include "mainwindow.h"
#include<QPalette>
#include<QFile>
#include<QTextStream>
#include<QDir>

LogInterface::LogInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogInterface)
{
    ui->setupUi(this);

    //设置字体颜色
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->hint_label->setPalette(pe);

    loadFile();
}

LogInterface::~LogInterface()
{
    delete ui;
}

bool LogInterface::logAdmit(QString user, QString password)
{
    if(user_list.find(user)==user_list.end() || user_list[user]!=password){
        ui->hint_label->setText("用户名或密码错误");
        return false;
    }
    else return true;
}

void LogInterface::on_exit_button_clicked()
{
    this->close();
}

void LogInterface::on_login_button_clicked()
{
    //判断是否成功登录，若成功则进入系统，否则进行错误提示
    if(logAdmit(ui->user->text(),ui->password->text())){
        this->close();
        MainWindow* mainwindow = new MainWindow;
        mainwindow->application_ptr = this->application_ptr;
        mainwindow->show();
    }
}

//路径需要改变
void LogInterface::loadFile()
{
    QFile file(QDir::currentPath() + "\\userList.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray content = file.readAll();
    file.close();
    QTextStream tstream(content);

    int size;
    tstream >> size;
    QString user,password;
    for(int i = 0 ; i < size ; ++i){
        tstream >> user >> password;
        this->user_list.insert(user,password);
    }

}
