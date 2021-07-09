#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "student.h"
#include "course.h"
#include "addstudentdialog.h"
#include "deldialog.h"
#include<QCloseEvent>
#include<QTextStream>

//QString read_process(const QString& )

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();//delete两个Qlist中指针指向的内存;将当前信息保存在文件中

    void addStudent(const QString& student_id, Student* student);
    void delStudent(const QString& student_id);//在qlist删除前delete指针指向的内存
    void addCourse(const QString& course_id, Course* course);

    void loadFile();
    void saveFile();

    void updateStudentGrade(Course *course, Student *student);

    //List中的数据应当在析构中delete
    QMap<QString, Student*> all_student_list;
    QMap<QString, Course*> all_course_list;

    QMap<QString, QString> course_map;

    QApplication* application_ptr;

private slots:

    void on_add_button_2_clicked();

    void on_delete_button_2_clicked();

    void on_update_button_2_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
